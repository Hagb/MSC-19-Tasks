#!/bin/bash

#      一个从重庆大学教务网获取课程表并进行处理的程序
#      Copyright (C) 2019 郭俊余(Hagb)
#
#      This program is free software: you can redistribute it and/or modify
#      it under the terms of the GNU General Public License as published by
#      the Free Software Foundation, either version 3 of the License, or
#      (at your option) any later version.
#
#      This program is distributed in the hope that it will be useful,
#      but WITHOUT ANY WARRANTY; without even the implied warranty of
#      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#      GNU General Public License for more details.
#
#      You should have received a copy of the GNU General Public License
#      along with this program.  If not, see <https://www.gnu.org/licenses/>.

. config
srgPass=efdfdfuuyyuuckjg
argUser=txt_dsdsdsdjkjkjc
argType=Sel_Type
loginPage=http://jxgl.cqu.edu.cn/_data/index_login.aspx
schemePage=http://jxgl.cqu.edu.cn/znpk/Pri_StuSel_rpt.aspx
cookiesfile=cookies
getEcryptedPass(){
	schoolcode="10611"
	yhm="$1"
	yhm=${yhm^^}
	pass=$(printf %s "$2" | md5sum)
	pass=${pass::30}
	pass=${pass^^}
	result=$(printf %s $yhm$pass$schoolcode | md5sum)
	result=${result::30}
	result=${result^^}
	echo $result
}
getScheme(){
	text="$(curl "$schemePage" -d 'Sel_XNXQ=20190&rad=on&px=1' -b "$cookiesfile" | iconv -f GBK -t UTF-8)"  
	if [[ "$text" =~ '/_help/Sorry_note.aspx?ID=001&amp;url=/ZNPK/PRI_STUSEL_RPT.ASPX&amp;ref=JXGL.CQU.EDU.CN' ]];
	then
		echo Cookies 过期/无效
		return 1
	else
		# 致读代码者：此处我不知道为什么用了eval最后会多个参数，而且这个参数是回车符（\r）！我感觉有点诡异……
		# 而将eval改为echo，输出看起来一切正常，并无法看到什么能导致这个回车符产生的东西。
		if eval python3 jsonScheme.py "$(
		printf %s "$text" | sed -n "/<tbody><tr >.*<\/tbody>/{
		s/^.*<tbody>//;
		s/ style='[^']*'//g;"'
		s/<td hidevalue='\''\([^>]*\)'\''><br><\/td>/<td >\1<br><\/td>/g;
		s/><br></></g;
		s/<br>//g;
		s/<td >/ '\''/g;
		s/<\/td>/'\'' /g;
		s/<[^>]*>/ /g;
		s/'\''\[[A-Za-z0-9]\+\]/&'\'' '\''/g;
		s/\[\([0-9]\+-[0-9]\+\|[0-9]\+\)节\]'\''/'\'' '\''\1'\''/g;
		p}'
		)" >scheme.json ;then
			echo scheme.json is available now.
			return 0
		else
			echo Generating scheme.json failed
			return 1
		fi
	fi
}
if [ -e "$cookiesfile" ];
then
	echo Try to use old cookies...
	getScheme && exit 0
fi
[ -z "$user" ] && echo 'Student ID (You can also set it in configure file "config"): ' && read user
[ -z "$pass" ] && echo 'Password (You can also set it in configure file "config"): ' && read -s password
text="$(curl -d "$argType=STU&$argUser=20191798&$argPass=$(getEcryptedPass "$user" "$password")" -c "$cookiesfile"  "$loginPage" | iconv -f GBK -t UTF-8 | sed -n '/<span id="divLogNote"><font color="White">/{s/.*<span id="divLogNote">//;s/<[^>]*>//g;p}')"
if [[ ! "$text" =~ '正在加载权限数据...' ]];
then
	echo 登陆失败！ >&2
	echo 错误信息： "$text" >&2
	exit 1
fi
echo 登陆成功！
getScheme


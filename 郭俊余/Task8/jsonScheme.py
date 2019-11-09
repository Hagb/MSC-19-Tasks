#!/usr/bin/env python3

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

import sys
import json
#if (len(sys.argv)-1)%15 != 0:
#    print("Scheme format error!")
#    print(len(sys.argv))
#    print(sys.argv[1::15])
#    exit(1)
# 致读代码者：这里我有一个疑问，见getScheme.sh第45、46行的注释。
scheme={}
for num in range((len(sys.argv)-1)//15):
    lesson=sys.argv[num*15+1:(num+1)*15+1]
    if not lesson[0].isdigit():
        print("Scheme format error!",file=sys.stderr)
        exit(1)
    for num2 in range(len(lesson)):
        if lesson[num2] == '':
            lesson[num2]=None
    detail={'teacher': lesson[10],
            'week': lesson[11], 
            'day': lesson[12], 
            'class': lesson[13],
            'place': lesson[14]}
    if not lesson[1] in scheme:
        scheme[lesson[1]]={'name': lesson[2],
                'credit': float(lesson[3]),
                'hours': float(lesson[4]),
                'teachingHours': float(lesson[5]),
                'practicalHours': float(lesson[6]),
                'type': lesson[7],
                'mode': lesson[8],
                'appraisal': lesson[9],
                'detail': [detail]
                }
    else:
        scheme[lesson[1]]['detail'].append(detail)
print(json.dumps(scheme, ensure_ascii=False, indent=4))
exit(0)

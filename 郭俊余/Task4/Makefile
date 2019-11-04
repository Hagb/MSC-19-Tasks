CN = tmpCN
OU = tmpOU
O = tmpO
L = tmpL
ST = tmlST
C = tmpC
PASSWORD = tmppass
KEYNAME = tmpkey
APKTOOL = apktool
all: catofyou.apk
keystore.keystore:
	printf '%s\n%s\n%s\n%s\n%s\n%s\n%s\n' "${CN}" "${OU}" "${O}" "${L}" "${ST}" "${C}" Y | keytool -genkey -alias "${KEYNAME}" -keystore $@ -storepass "${PASSWORD}"

bestofyou.apk:
	wget https://hack.lug.ustc.edu.cn/media/810177b6-c445-5e5c-b719-6340c7d11ad2/bestofyou.apk -O $@

cat.mp3:
	wget https://www.microsoftstudent.club/uploads/cat.mp3 -O $@

catofyou.apk: bestofyou.apk cat.mp3 keystore.keystore 
	-rm -r bestofyou
	${APKTOOL} d bestofyou.apk -s
	cp cat.mp3 bestofyou/res/raw/wind.mp3
	${APKTOOL} b bestofyou 
	jarsigner -keystore keystore.keystore bestofyou/dist/bestofyou.apk "${KEYNAME}" -storepass "${PASSWORD}"
	cp bestofyou/dist/bestofyou.apk $@

clean: 
	rm -r keystore.keystore bestofyou.apk res catofyou.apk cat.mp3 bestofyou

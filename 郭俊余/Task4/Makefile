CN = tmpCN
OU = tmpOU
O = tmpO
L = tmpL
ST = tmlST
C = tmpC
PASSWORD = tmppass
KEYNAME = tmpkey
all: catofyou.apk
keystore.keystore:
	printf '%s\n%s\n%s\n%s\n%s\n%s\n%s\n' "${CN}" "${OU}" "${O}" "${L}" "${ST}" "${C}" Y | keytool -genkey -alias "${KEYNAME}" -keystore $@ -storepass "${PASSWORD}"

bestofyou.apk:
	wget https://hack.lug.ustc.edu.cn/media/810177b6-c445-5e5c-b719-6340c7d11ad2/bestofyou.apk -O $@

res/raw/cat.mp3:
	mkdir -p res/raw
	wget https://www.microsoftstudent.club/uploads/cat.mp3 -O $@

catofyou.apk: bestofyou.apk res/raw/cat.mp3 keystore.keystore
	cp bestofyou.apk catofyou.apk
	jar uf $@ res/raw/cat.mp3 $@
	jarsigner -verbose -keystore keystore.keystore $@ "${KEYNAME}" -storepass "${PASSWORD}"

clean: 
	rm -r keystore.keystore bestofyou.apk res catofyou.apk

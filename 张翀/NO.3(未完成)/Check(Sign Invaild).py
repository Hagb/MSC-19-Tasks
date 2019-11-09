import requests
import json
import hashlib
import random
import string
import time
import datetime
import base64
from urllib import parse
                                                                                                                                                             
url = "https://api.ai.qq.com/fcgi-bin/vision/vision_porn"
app_key = "ZcU5JnbegJ3TxM0b"
app_id = 2123715780
time_stamp = int(time.time())
nonce_str = "".join(random.sample(string.ascii_letters + string.digits, 10))
with open(".\judge.jpg","rb") as f :
    image = base64.b64encode(f.read())

dist = [["app_id",app_id],["image",image],["time_stamp",time_stamp],["nonce_str",nonce_str],["sign",""]]
dist.sort()

def getReqSign() :
    sign = ""
    for i in range(0,len(dist)) :
        if dist[i][0] != "sign" :
            sign = sign + dist[i][0] + '=' + parse.quote(str(dist[i][1])) + '&'
    sign = sign + "app_key=" + app_key
    sign = hashlib.md5(sign.encode(encoding = "UTF-8")).hexdigest().upper()
    ans = {}
    for i in range(0,len(dist)) :
        ans[dist[i][0]] = dist[i][1]
    ans["sign"] = sign
    return ans

msg = getReqSign()
r = requests.post(url,msg)
print(r.json())

input()







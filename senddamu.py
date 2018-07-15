import urllib
import urllib.request
import requests
import json
import time
import os
import sys

class Config(object):
    def __init__(self):
        self.reload()
        pass

    # 获取配置项
    def get(self, key, module=''):
        if module == '':
            # 判断是否存在该Key
            if key in self.config:
                return str(self.config[key])
            else:
                return None
        else:
            # 判断是否存在module
            if module not in self.config:
                return None
            # 是否存在Key
            if key not in self.config[module]:
                return None

            return str(self.config[module][key])
        pass

    def set(self, key, value, module=''):
        if module == '':
            self.config[key] = value
        else:
            if module in self.config:
                self.config[module][key] = value
            else:
                self.config[module] = {
                    key: value
                }

        file = open('config.json', 'w')
        json.dump(obj=self.config, fp=file, ensure_ascii=False, indent=4)
        pass

    # 从文件中读取配置对象
    def reload(self):
        configPath = 'config.json'
        configFile = open(configPath, encoding='utf-8')
        self.config = json.load(configFile)
class Danmu(object):
    def __init__(self):
        self.config = Config()
        self.httpConfig = {
            'getUrl': 'http://api.live.bilibili.com/ajax/msg',
            'sendUrl': 'http://api.live.bilibili.com/msg/send',
            'header': {
                "Accept":"text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
                "Accept-Encoding":"utf-8",
                "Accept-Language":"zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3",
                "Connection":"keep-alive",
                "Cookie": self.config.get('cookie'),
                "Host":"api.live.bilibili.com",
                "Referer":"http://live.bilibili.com/" + self.config.get('roomId'),
                "User-Agent":"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:32.0) Gecko/20100101 Firefox/32.0"
            }
        }
        self.sendLock = False

    def get(self):
        # 准备数据
        roomId = self.config.get('roomId')
        postData = urllib.parse.urlencode({	'token:': '', 'csrf_token:': '', 'roomid': roomId }).encode('utf-8')

        # 发送请求
        request = urllib.request.Request(self.httpConfig['getUrl'], postData, self.httpConfig['header'])
        response = json.loads(urllib.request.urlopen(request).read().decode('utf-8'))

        # 获取最后的弹幕时间
        configTimestamp = self.config.get(module='danmu', key='timestamp')
        if configTimestamp == None:
            configTimestamp = 0
        else:
            configTimestamp = float(configTimestamp)

        if 'code' in response and response['code'] == 0:
            # 解析弹幕
            result = []
            for danmu in response['data']['room']:

                # 判断弹幕是否被处理过
                thisTimestamp = time.mktime(time.strptime(danmu['timeline'], "%Y-%m-%d %H:%M:%S"))
                if configTimestamp >= thisTimestamp:
                    continue
                
                self.config.set(module='danmu', key='timestamp', value=thisTimestamp)
                
                result.append({
                    'name': danmu['nickname'],
                    'time': danmu['timeline'],
                    'uid': str(danmu['uid']),
                    'text': danmu['text']
                })
                pass
            return result
        else:
            raise Exception('Cookie 无效')

    def send(self, text):
        elapsedTime = 0
        while self.sendLock:
            time.sleep(1)
            # 判断等待超时
            elapsedTime += 1
            if (elapsedTime > 30):
                return None
        
        # 判断长度
        lengthLimit = 20
        if len(text) > lengthLimit:
            for i in range(0, len(text), lengthLimit):
                self.send(text[i:i + lengthLimit])
                time.sleep(1.5)
            return True
        
        # 准备数据
        self.sendLock = True
        try:
            roomId = self.config.get('roomId')
            postData = (urllib.parse.urlencode({
                            'color': '16777215',
                           # 'csrf_token': '5f9e891cfd70c2c6a703fd494bf69dc7',
                            'fontsize': '25',
                            'mode': '1',
                            'msg': text,
                            'rnd': '1512718534',
                            'roomid': roomId
                        }).encode('utf-8'))

            psdata={
                            'color': '16777215',
                            'csrf_token': '5f9e891cfd70c2c6a703fd494bf69dc7',
                            'fontsize': '25',
                            'mode': '1',
                            'msg': text,
                            'rnd': '1512718534',
                            'roomid': roomId
                    }

            # 发送请求
            '''
            request = urllib.request.Request(self.httpConfig['sendUrl'], postData, self.httpConfig['header'])
            response = json.loads(urllib.request.urlopen(request).read().decode('utf-8'))
            print(response)
            
            '''
            cookie={'Cookie':'l=v; LIVE_BUVID=AUTO9115296677131525; Hm_lvt_8a6e55dbd2870f0f5bc9194cddf32a02=1529667823,1529678970,1529719880; finger=7b4f413b; buvid3=8933D0B8-6007-4CE8-86BA-C93029CCD26416479infoc; sid=luecjskq; fts=1529669115; DedeUserID=311817936; DedeUserID__ckMd5=cca4969724abe2bb; SESSDATA=03bf401f%2C1532261056%2C82174446; bili_jct=5f9e891cfd70c2c6a703fd494bf69dc7; Hm_lpvt_8a6e55dbd2870f0f5bc9194cddf32a02=1529722625; _dfcaptcha=0691ef63ed3afa8e000cc79433fa186b; UM_distinctid=1642a729295c8-0408a57676b7d6-143e7140-fa000-1642a7292961'}
            re=requests.post(self.httpConfig['sendUrl'],data=psdata,cookies=cookie)
            print(re.text)
            
            
            #return 'code' in response and response['code'] == 0
        except Exception as e:
            raise e
        finally:
            self.sendLock = False

  

if __name__ == '__main__':
    dan=Danmu()
    dan.config.reload()
    wenzi=str(sys.argv[1])
    dan.send(wenzi)

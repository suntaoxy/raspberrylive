#coding: utf-8
'''
Download subtitles using SPlayer API
@author: me@qzane.com
https://docs.google.com/document/d/1ufdzy6jbornkXxsD-OGl3kgWa4P9WO5NZb6_QYZiGI0/preview#
射手影音智能字幕查询API（JSON）
功能: 根据客户端提交的信息，返回匹配字幕信息和字幕数据包
通讯协议: HTTP POST
接口地址: https://www.shooter.cn/api/subapi.php
上行参数:
|参数名称|类型|含义|备注|示例|
|--------|----|----|----|----|
|filehash|String|视频文件的hash码|必填|参考“文件Hash算法协议”|
|pathinfo|String|视频文件的所在路径名和文件名|必填|D:/Matrix.720p.HDTV.X264-DIMENSION/md.mkv|
|format|String|结果输出格式，值必须为 json|必填|json|
|lang|String|字幕语言|可选|eng或者chn|
注：参数均以标准的RFC 3986协议编码传送。即以文字的UTF8值进行URLEncode编码传送。例如“中国”，将以“%E4%B8%AD%E5%9B%BD”传送。
下行数据:
尚不能提供字幕时将返回一个字节，值为0xff(-1)。
可提供字幕时会返回json格式的Subinfo结构的Array数据，结构如下：
type Fileinfo struct {
  Ext    string // 文件扩展名
  Link   string // 文件下载链接
}
type Subinfo struct {
  Desc   string // 备注信息
  Delay  int32  // 字幕相对于视频的延迟时间，单位是毫秒
  Files  []Fileinfo  // 包含文件信息的Array。 注：一个字幕可能会包含多个字幕文件，例如：idx+sub格式
}
https://docs.google.com/document/d/1w5MCBO61rKQ6hI5m9laJLWse__yTYdRugpVyz4RzrmM/preview
SVPlayer视频文件hash算法 （草）
Version. 0.1    Date: 2008-11-04
方案
取文件第4k位置，再根据floor( 文件总长度/3 )计算，取中间2处，再取文件结尾倒数第8k的位置， 4个位置各取4k区块做md5。共得到4个md5值，均设为索引。可以进行智能匹配。 （可以应用于不完全下载的p2p文件）
'''

import os
import sys
import json
import hashlib
import requests

def fileHash(fname):
    file = open(fname, 'rb')
    file.seek(0,2)
    length = file.tell()
    hash = []
    for i in [4096, int(length*2/3), int(length/3), length-8192]:
        file.seek(i, 0)
        buf = file.read(4096)
        hash.append(hashlib.md5(buf).hexdigest())
    return ';'.join(hash)
    
def makeData(fname, lang='chn'):
    ''' makeData(fname, lang)
            lang = 'chn' or 'eng' '''
    data = {}
    data['filehash']=fileHash(fname)
    data['pathinfo']=fname
    data['format']='json'
    data['lang']=lang
    return data
    
def getSubInfo(data):
    url = r'https://www.shooter.cn/api/subapi.php'
    try:
        q = requests.post(url, data=data)
    except:
        sys.stderr.write('network error!\n')
        sys.exit()
        
    if q.content == b'\xff':
        return None
    else:
        res = json.loads(q.text)
        info = [] #[[(url, ext)], delay, desc]
        for sub in res:
            urls = [(file['Link'], file['Ext']) for file in sub['Files']]
            delay = sub['Delay']
            desc = sub['Desc']
            info.append([urls, delay, desc])
        return info        
        
def writeSub(info, fname = 'D:/Matrix.mkv' ,lang='chn'):
    ''' lang = 'chn' or 'eng' '''
    try:
        fname = fname[:fname.rfind('.')]
    except:
        pass
        
    for no, subs in enumerate(info):
        name = fname + '.' + lang + str(no)
        if len(subs[0]) == 1:
            url = subs[0][0][0]
            try:
                data = requests.get(url).content
            except:                
                sys.stderr.write('network error while downloading !\n')
            with open(name+'.'+subs[0][0][1],'wb') as f:
                f.write(data)
        else:
            for noo, sub in enumerate(subs[0]):
                url = sub[0]
                try:
                    data = requests.get(url).content                    
                except:                
                    sys.stderr.write('network error while downloading !\n')
                with open(name+'.'+str(noo)+'.'+sub[1],'wb') as f:
                    f.write(data)
        sys.stdout.write("Subtitle: {}\nDelay: {}\nDescription: {}\n\n".format(name, subs[1], subs[2]))
        sys.stdout.flush()
        
def downloadSub(fname, lang='chn'):
    ''' lang = 'chn' or 'eng' or 'all' '''
    data = makeData(fname, lang)
    info = getSubInfo(data)
    if info:
        writeSub(info, fname, lang)
    else:
        sys.stdout.write("no subtitle found\n")
        sys.stdout.flush()
        
if __name__ == '__main__':
    downloadSub(sys.argv[1])
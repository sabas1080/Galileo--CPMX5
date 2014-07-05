#!/usr/local/bin/python2.7
    
#-*-coding:utf8-*-
import urllib2
import sys
#-*-import time, datetime-*-
import json

valor=(sys.argv[1]);
print(valor)

class Client(object):
    api_url = "http://api.carriots.com/streams"
 
    def __init__ (self, api_key = None, client_type = 'json'):
        self.client_type = client_type
        self.api_key = api_key
        self.content_type = "application/vnd.carriots.api.v2+%s" % (self.client_type)
        self.headers = {'User-Agent': 'Galileo-Carriots',
                        'Content-Type': self.content_type,
                        'Accept': self.content_type,
                        'Carriots.apikey': self.api_key}
 
    def send (self, data):
        self.data = json.dumps(data)
        request = urllib2.Request(Client.api_url, self.data, self.headers)
        self.response = urllib2.urlopen(request)
        return self.response
 
 
def main():
    ON = 1
    DEVICE = "ID dispositivo"
    APIKEY = "APIKEY de escritura"
    lights=ON
    a=0; 
    client_carriots = Client (APIKEY)
    data = {"protocol":"v2","device":DEVICE,"at":"now","data":{"light":valor}}
    carriots_response=client_carriots.send(data)
 
if __name__ == '__main__':
    main()
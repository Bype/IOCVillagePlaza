#!/usr/bin/python

import urllib2
import os
import subprocess

json = eval(urllib2.urlopen("http://localhost:8000/json").read())   

for page in json:
    folder = '/home/dolivari/media/render/'+page["lang"]+'/'+page["topic"]
    if not os.path.exists(folder):
        os.makedirs(folder)
    print folder+'/'+str(page["pos"])+'.jpg'
    subprocess.call(['webkit2png', '-g', '1280','800','-f','jpg', '-o',folder+'/'+str(page["pos"])+'.jpg',page["url"]])
        
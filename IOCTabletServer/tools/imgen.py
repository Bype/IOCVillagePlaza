#!/usr/bin/python

import urllib2
import os
import subprocess

json = eval(urllib2.urlopen("http://ioc.bype.org:8000/json").read())   

for page in json:
    folder = '/home/dolivari/media/render/'+page["lang"]+'/'+page["topic"]
    if not os.path.exists(folder):
        os.makedirs(folder)
    path = folder+'/'+str(page["pos"])+'.jpg'
    if os.path.exists(path):
        print "already exists"
    else:
        subprocess.call(['webkit2png', '-g', '1280','800','-f','jpg', '-o',path,page["url"]])
        
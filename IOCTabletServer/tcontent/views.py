# Create your views here.
import os
from models import Topic
from models import Page
from models import Text
from django.conf import settings
from django.http import HttpResponse
from django.core.exceptions import ObjectDoesNotExist
from django.template import Context, loader
from django.utils import simplejson
from django.core.cache import cache
import json

def text(request, topic, lang, page):
    try:
        text = Text.objects.get(lang=lang, page=Page.objects.get(pos=page, topic=Topic.objects.get(name=topic))).text
        text = text.replace('\\n', '\n'); 
    except ObjectDoesNotExist:
        text = "Not found"
    return HttpResponse(text, mimetype="text/plain")

def title(request, topic, lang, page):
    try:
        title = Text.objects.get(lang=lang, page=Page.objects.get(pos=page, topic=Topic.objects.get(name=topic))).title
        title = title.replace('\\n', '\n'); 
    except ObjectDoesNotExist:
        title = "Not found"
    return HttpResponse(title, mimetype="text/plain")

def imageurl(request, topic, lang, page):
    image = "http://" + request.get_host()
    image += "/media/" + topic + "/"   
    image += Page.objects.get(pos=page, topic=Topic.objects.get(name=topic)).image
    return HttpResponse(image, mimetype="text/plain")

def slideshow(request, topic, lang):
    t = loader.get_template('slideshow.html')
    c = Context({
                 'topic':topic,
                 'lang':lang,
                 'imgidx':[i + 1 for i in range(len(Page.objects.filter(topic=Topic.objects.get(name=topic))))],
                 })
    return HttpResponse(t.render(c))

def render(request, topic, lang, page):
    t = loader.get_template('render.html')
    try:
        text = Text.objects.get(lang=lang, page=Page.objects.get(pos=page, topic=Topic.objects.get(name=topic))).text
        range = 1
        if (len(text) < 256):
            range = 2
        else :
            if (len(text) < 512):
                range = 3
            else : 
                if (len(text) < 768):
                    range = 4
                else:
                    if (len(text) < 1024):
                        range = 5
                    else :
                        range = 6
        if (lang == "ru"):
            range = range+1
        textrange = "t"+str(range)
        
    except ObjectDoesNotExist:
        text = "Not found"
        textrange = "t"
    try:
        title = Text.objects.get(lang=lang, page=Page.objects.get(pos=page, topic=Topic.objects.get(name=topic))).title
        title = title.replace('\\n', '\n'); 
    except ObjectDoesNotExist:
        title = "Not found"
    c = Context({
                 'topic':topic,
                 'lang':lang,
                 'page':page,
                 'title':title,
                 'text':text,
                 'textrange':textrange,
                 'imgname':Page.objects.get(pos=page, topic=Topic.objects.get(name=topic)).image
                 })
    return HttpResponse(t.render(c))


def index(request):
    t = loader.get_template('index.html')
    c = Context({
                'topics':Topic.objects.all(),
                'langs' : ['en', 'fr', 'es', 'cn', 'ar', 'ru']
    })
    return HttpResponse(t.render(c))

def img(request, topic, lang, page):
    import Image, ImageDraw, ImageFont, textwrap
    from django.utils.text import normalize_newlines
    from django.utils.safestring import mark_safe
       
    dir = settings.MEDIA_ROOT + '/render/' + lang + '/' + topic;
     
    if os.path.exists(dir + '/' + page + '_s.jpg'):
        return HttpResponse(open(dir + '/' + page + '_s.jpg'), mimetype="image/jpeg")
       
    ''' A View that Returns a PNG Image generated using PIL'''
  
    image = Image.open(Page.objects.get(pos=page, topic=Topic.objects.get(name=topic)).image)
    title = Text.objects.get(lang=lang, page=Page.objects.get(pos=page, topic=Topic.objects.get(name=topic))).title
    text = Text.objects.get(lang=lang, page=Page.objects.get(pos=page, topic=Topic.objects.get(name=topic))).text
    im = Image.new('RGBA', (1280, 800), (255, 255, 255, 255))
    draw = ImageDraw.Draw(im)
    im.paste(image, (0, 0))
    textFont = ImageFont.truetype("/home/dolivari/IOCVillagePlaza/IOCTabletServer/fonts/HelveticaLTStd-Roman.otf", 22)
    if len(title) < 32:
        titleFont = ImageFont.truetype("/home/dolivari/IOCVillagePlaza/IOCTabletServer/fonts/HelveticaNeueLTCom-BlkCn.ttf", 40)
    else:
        titleFont = ImageFont.truetype("/home/dolivari/IOCVillagePlaza/IOCTabletServer/fonts/HelveticaNeueLTCom-BlkCn.ttf", 34)
    width, height = titleFont.getsize(title)
    draw.text((1260 - width, 50), title, font=titleFont, fill=(32, 32, 32, 255))
    text = mark_safe(normalize_newlines(text))
    paragraphs = text.split('\n')
    width, height = textFont.getsize(text)
    y_text = 450 - (len(text) / 58) * height   
    for par in paragraphs:
        if(len(par) == 0):
            y_text += height
        lines = textwrap.wrap(par, width=54)
        for line in lines:
            width, height = textFont.getsize(line)
            draw.text((705, y_text), line, font=textFont, fill=(32, 32, 32, 255))
            y_text += height
    
    del draw # I'm done drawing so I don't need this anymore
    # We need an HttpResponse object with the correct mimetype
    response = HttpResponse(mimetype="image/jpeg")
    # now, we tell the image to save as a PNG to the 
    # provided file-like object
    im.thumbnail((640, 400), Image.ANTIALIAS)
    im.save(response, 'jpeg', quality=90)
    if not os.path.exists(dir):
        os.makedirs(dir)
    im.save(open(dir + '/' + page + '_s.jpg', 'w+'), 'jpeg', quality=90)
    return response # and we're done!

def json(request):
    data = []
    for text in Text.objects.all():
        page = {'topic': text.page.topic.name, 'lang':text.lang, 'pos':text.page.pos}
        page['url'] = 'http://ioc.bype.org/render/' + text.page.topic.name + '/' + text.lang + '/' + str(text.page.pos) + '.html'        
        data.append(page)
    return HttpResponse(simplejson.dumps(data), content_type="application/json")

import redis

def stat(request, topic, lang, page):
        r = redis.Redis(host='192.168.122.1', port=6379, db=0)
        r.incr(lang+'/'+topic+'/'+page)
        data = {'result':'success'}
        return HttpResponse(simplejson.dumps(data), content_type="application/json")
    
        

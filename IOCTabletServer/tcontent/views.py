# Create your views here.
from models import Topic
from models import Page
from models import Text
from django.http import HttpResponse
from django.core.exceptions import ObjectDoesNotExist

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


def image(request, topic, lang, page):
    import Image, ImageDraw, ImageFont,textwrap
    from django.utils.text import normalize_newlines
    from django.utils.safestring import mark_safe
       
    ''' A View that Returns a PNG Image generated using PIL'''
  
    image = Image.open('static/' + topic + "/" + Page.objects.get(pos=page, topic=Topic.objects.get(name=topic)).image)
    title = Text.objects.get(lang=lang, page=Page.objects.get(pos=page, topic=Topic.objects.get(name=topic))).title
    text = Text.objects.get(lang=lang, page=Page.objects.get(pos=page, topic=Topic.objects.get(name=topic))).text
    im = Image.new('RGBA', (1280, 800), (255, 255, 255, 255))
    draw = ImageDraw.Draw(im)
    im.paste(image, (0, 0))
    textFont = ImageFont.truetype("fonts/HelveticaLTStd-Roman.otf", 24)
    titleFont = ImageFont.truetype("fonts/HelveticaNeueLTCom-BlkCn.ttf", 40)
    width, height = titleFont.getsize(title)
    draw.text((1260-width, 50), title, font=titleFont, fill=(32, 32, 32, 255))
    text =  mark_safe(normalize_newlines(text))
    paragraphs = text.split('\n')
    y_text = 150        
    for par in paragraphs:
        if(len(par) == 0):
            y_text += height
        lines = textwrap.wrap(par, width = 45)
        for line in lines:
            width, height = textFont.getsize(line)
            draw.text((705, y_text), line, font=textFont, fill=(32, 32, 32, 255))
            y_text += height
    
    del draw # I'm done drawing so I don't need this anymore
    # We need an HttpResponse object with the correct mimetype
    response = HttpResponse(mimetype="image/jpeg")
    # now, we tell the image to save as a PNG to the 
    # provided file-like object
    im.save(response, 'jpeg',quality=90)

    return response # and we're done!

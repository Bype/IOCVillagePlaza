# Create your views here.
from tcontent.models import Topic
from tcontent.models import Page
from tcontent.models import Text
from django.http import HttpResponse

def text(request, topic, lang, page):
    
    text = Text.objects.get(lang=lang,
                            page=Page.objects.get(pos=page,
                                                  topic=Topic.objects.get(name=topic))).text
    text = text.replace('\\n', '\n'); 
    return HttpResponse(text, mimetype="text/plain")

def title(request, topic, lang, page):
    title = Text.objects.get(lang=lang,
                            page=Page.objects.get(pos=page,
                                                  topic=Topic.objects.get(name=topic))).title
    title = title.replace('\\n', '\n'); 
    return HttpResponse(title, mimetype="text/plain")

def imageurl(request, topic, lang, page):
    image = "http://" + request.get_host()
    image += "/media/" + topic + "/"   
    image += Page.objects.get(pos=page, topic=Topic.objects.get(name=topic)).image
    return HttpResponse(image, mimetype="text/plain")


def image(request, topic, lang, page):
    import Image, ImageDraw, ImageFont
    def draw_word_wrap(draw, text, xpos=0, ypos=0, max_width=130,
                       fill=(0, 0, 0), font=ImageFont.load_default()):
        '''Draw the given ``text`` to the x and y position of the image, using
        the minimum length word-wrapping algorithm to restrict the text to
        a pixel width of ``max_width.``
        '''
        text_size_x, text_size_y = draw.textsize(text, font=font)
        remaining = max_width
        space_width, space_height = draw.textsize(' ', font=font)
        # use this list as a stack, push/popping each line
        output_text = []
        # split on whitespace...    
        for word in text.split(None):
            word_width, word_height = draw.textsize(word, font=font)
            if( word_width + space_width > remaining or word=='<br>'):
                output_text.append(word)
                remaining = max_width - word_width
            else:
                if not output_text:
                    output_text.append(word)
                else:
                    output = output_text.pop()
                    if(output == '<br>'):
                        output = '%s' % word
                    else:
                        output += ' %s' % word
                    output_text.append(output)
                remaining = remaining - (word_width + space_width)
        for text in output_text:
            draw.text((xpos, ypos), text, font=font, fill=fill)
            ypos += text_size_y
        
    ''' A View that Returns a PNG Image generated using PIL'''
   # tab = Image.open('static/tab.png',)
    image = Image.open('static/'+ topic + "/"+Page.objects.get(pos=page, topic=Topic.objects.get(name=topic)).image)
    title = Text.objects.get(lang=lang, page=Page.objects.get(pos=page, topic=Topic.objects.get(name=topic))).title
    text = Text.objects.get(lang=lang, page=Page.objects.get(pos=page, topic=Topic.objects.get(name=topic))).text
    im = Image.new('RGBA', (800, 1280), (248, 248, 248, 255))
    draw = ImageDraw.Draw(im)
    im.paste(image,(0,0))
   # im.paste(tab,(0,0),tab)      
    textFont = ImageFont.truetype("fonts/HelveticaLTStd-Roman.otf", 24)
    titleFont = ImageFont.truetype("fonts/HelveticaNeueLTCom-BlkCn.ttf", 50)
    draw.text((50, 700), title, font=titleFont, fill=(32, 32, 32, 255))
    draw_word_wrap(draw, text, 50, 750, 700, font=textFont, fill=(32, 32, 32, 255))
    del draw # I'm done drawing so I don't need this anymore
    # We need an HttpResponse object with the correct mimetype
    response = HttpResponse(mimetype="image/png")
    # now, we tell the image to save as a PNG to the 
    # provided file-like object
    im.save(response, 'png')

    return response # and we're done!

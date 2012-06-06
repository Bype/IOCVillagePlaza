#!/bin/python
from reportlab.lib.styles import ParagraphStyle as PS  
from reportlab.lib.pagesizes import A4, landscape
from reportlab.platypus import SimpleDocTemplate, Image, PageBreak, Paragraph
from reportlab.lib.units import cm
import os, re

def sort_nicely(l): 
  """ Sort the given list in the way that humans expect. 
  """ 
  convert = lambda text: int(text) if text.isdigit() else text 
  alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ] 
  l.sort(key=alphanum_key) 

MEDIA_ROOT = '/home/dolivari/media'
TOPIC_CHOICES = { 'community_dev' : 'Community Development',
                   'giving_winning' : 'Giving is Winning',
                   'aids_prevention' : 'HIV & AIDS prevention',
                   'truce' : 'Olympic Truce',
                   'women_sport' : 'Women in sport',
                   'sport_sustain' : 'Sustainability',
                   'museum' : 'Donations to Olympic Museum',
                   'olympic_value' : 'Olympic Values',
                   'words_olympians' : 'Words of Olympians',
                   'sexual_harassment' : 'Sexual Harassment and Abuse',
                   'healthy_body' : 'Healthy Body Image',
                   'irregular_betting' : 'Fight irregular sports betting'
                    }

doc = SimpleDocTemplate("/tmp/tabletVP.pdf", pagesize=landscape(A4),
                            rightMargin=50, leftMargin=50,
                            topMargin=50, bottomMargin=50, orientation='landscape')
titled = PS(name='centered',
    fontSize=30,
    leading=16,
    alignment=1,
    spaceAfter=20)

centered = PS(name='centered',
    fontSize=15,
    leading=16,
    alignment=1,
    spaceAfter=20)

Story = []

topics = os.listdir(MEDIA_ROOT + '/render/en')
for tp in topics:
    
    pgs = os.listdir(MEDIA_ROOT + '/render/en/' + tp)
    sort_nicely(pgs)
    pgnum = 1
    print tp
    for pg in pgs:
        if re.match(r'\d*.jpg', pg):
            print pg
            im = Image(MEDIA_ROOT + '/render/en/' + tp + '/' + pg, 21.7 * cm, 13.5* cm)
            Story.append(Paragraph('<b>'+TOPIC_CHOICES[tp]+'</b></br>', titled))
            Story.append(im)
            Story.append(Paragraph(str(pgnum) + ' / '+str(len(pgs)), centered))
            pgnum +=1
            Story.append(PageBreak())
    

doc.build(Story)

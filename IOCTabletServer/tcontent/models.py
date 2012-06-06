from django.db import models
from django.core.exceptions import ObjectDoesNotExist
from django.db.models.signals import pre_save
from django.dispatch import receiver
from django.conf import settings
from django.utils.safestring import mark_safe 
import os

# Create your models here.
class Topic(models.Model):
    TOPIC_CHOICES = (('community_dev', 'Community Development'),
                   ('giving_winning', 'Giving is Winning'),
                   ('aids_prevention', 'HIV & AIDS prevention'),
                   ('truce', 'Olympic Truce'),
                   ('women_sport', 'Women in sport'),
                   ('sport_sustain', 'Sustainability'),
                   ('museum', 'Donations to Olympic Museum'),
                   ('olympic_value', 'Olympic Values'),
                   ('words_olympians','Words of Olympians'),
                   ('sexual_harassment','Sexual Harassment and Abuse'),
                   ('healthy_body','Healthy Body Image'),
                   ('irregular_betting','Fight irregular sports betting')
                    )
    name = models.CharField(max_length=64, choices=TOPIC_CHOICES)
    def __unicode__(self):
        return u'%s' % (self.name)
    
class Page(models.Model):
    topic = models.ForeignKey(Topic)
    pos = models.IntegerField()
    image = models.FileField(upload_to='ioc_img')
    def __unicode__(self):
        try:
            return u'%s > %s > %s' % (self.topic.name, self.pos, Text.objects.get(lang='en', page=self).title)
        except ObjectDoesNotExist:
            return u'%s > %s > ?' % (self.topic.name, self.pos)
    

class Text(models.Model):
    LANG_CHOICES = (('en', 'English'),
                    ('fr', 'French'),
                    ('es', 'Spanish'),
                    ('ru', 'Russian'),
                    ('ar', 'Arabic'),
                    ('cn', 'Chinese'))
    page = models.ForeignKey(Page)
    lang = models.CharField(max_length=2, choices=LANG_CHOICES)
    title = models.CharField(max_length=256)
    text = models.CharField(max_length=1024)
    def __unicode__(self):
        return u'%s > %s > %s' % (self.page.topic.name, self.page.pos, self.lang)
    def display_myText(self): 
        return mark_safe(self.text)
    def display_myTitle(self): 
        return mark_safe(self.text)
    
    def clean(self):
        aPath = settings.MEDIA_ROOT + '/render/' + self.lang + '/' + self.page.topic.name + '/' + str(self.page.pos) + '.jpg'
        if os.path.exists(aPath):
            os.remove(aPath)

from django.db import models
from django.core.exceptions import ObjectDoesNotExist

# Create your models here.
class Topic(models.Model):
    name = models.CharField(max_length=64)
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
    title = models.CharField(max_length=128)
    text = models.CharField(max_length=800)
    def __unicode__(self):
        return u'%s > %s > %s' % (self.page.topic.name, self.page.pos, self.lang)
     

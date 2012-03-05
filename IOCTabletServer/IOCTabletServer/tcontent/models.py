from django.db import models

# Create your models here.
class Topic(models.Model):
    name= models.CharField(max_length=32)
    def __unicode__(self):
        return u'%s' % (self.name)
    
class Page(models.Model):
    topic = models.ForeignKey(Topic)
    pos = models.IntegerField()
    title = models.CharField(max_length=32)
    image = models.CharField(max_length=64)
    def __unicode__(self):
        return u'%s' % (self.title)
    

class Text(models.Model):
    page = models.ForeignKey(Page)
    lang = models.CharField(max_length=5)
    title = models.CharField(max_length=32)
    text =  models.CharField(max_length=720)
    def __unicode__(self):
        return u'%s > %s > %s' % (self.page.topic.name,self.page.title,self.lang)
    
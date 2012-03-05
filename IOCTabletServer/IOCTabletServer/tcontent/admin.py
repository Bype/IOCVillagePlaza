from tcontent.models import Topic
from tcontent.models import Page
from tcontent.models import Text
from django.contrib import admin

class TopicAdmin(admin.ModelAdmin):
    list_display = ('name',)
    
admin.site.register(Topic, TopicAdmin)

class TextInline(admin.TabularInline):
    model = Text

class PageAdmin(admin.ModelAdmin):
    fields = ('topic', 'pos','title', 'image')
    list_filter = ('topic__name',)
    ordering=('pos',)
    inlines=[TextInline,]

    
admin.site.register(Page, PageAdmin)

class TextAdmin(admin.ModelAdmin):
    fields = ('page', 'lang', 'title', 'text')
    
admin.site.register(Text, TextAdmin)

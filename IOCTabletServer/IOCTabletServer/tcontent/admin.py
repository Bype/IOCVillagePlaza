from tcontent.models import Topic
from tcontent.models import Page
from tcontent.models import Text
from django.contrib import admin
from django import forms


class TextModelForm(forms.ModelForm):
    text = forms.CharField(widget=forms.Textarea )
    class Meta:
        model = Text

class TextInline(admin.TabularInline):
    model = Text
    form = TextModelForm

class TextAdmin(admin.ModelAdmin):
    fields = ('page', 'lang', 'title', 'text')
    form = TextModelForm
    
admin.site.register(Text, TextAdmin)


class PageAdmin(admin.ModelAdmin):
    fields = ('topic', 'pos','title', 'image')
    list_filter = ('topic__name',)
    ordering=('pos',)
    inlines=[TextInline,]
    
admin.site.register(Page, PageAdmin)


class PageInline(admin.TabularInline):
    model = Page
   
    
class TopicAdmin(admin.ModelAdmin):
    list_display = ('name',)
    inlines=[PageInline,]

    
admin.site.register(Topic, TopicAdmin)

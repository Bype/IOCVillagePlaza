from tcontent.models import Topic
from tcontent.models import Page
from tcontent.models import Text
from django.contrib import admin
from django import forms
import os
import Image
from django.contrib.admin.widgets import AdminFileWidget
from django.utils.translation import ugettext as _
from django.utils.safestring import mark_safe

class TextModelForm(forms.ModelForm):
    text = forms.CharField(widget=forms.Textarea)
    class Meta:
        model = Text

class TextInline(admin.TabularInline):
    model = Text
    form = TextModelForm

class TextAdmin(admin.ModelAdmin):
    fields = ('page', 'lang', 'title', 'text')
    form = TextModelForm
    
admin.site.register(Text, TextAdmin)

class AdminImageWidget(AdminFileWidget):
    def render(self, name, value, attrs=None):
        output = []
        if value and getattr(value, "url", None):
            
            image_url = value.url
            file_name = str(value)
            
            # defining the size
            size = '100x100'
            x, y = [int(x) for x in size.split('x')]
            
            # defining the filename and the miniature filename
            filehead, filetail = os.path.split(value.path)
            basename, format = os.path.splitext(filetail)
            miniature = basename + '_' + size + format
            filename = value.path
            miniature_filename = os.path.join(filehead, miniature)
            filehead, filetail = os.path.split(value.url)
            miniature_url = filehead + '/' + miniature
            
            # make sure that the thumbnail is a version of the current original sized image
            if os.path.exists(miniature_filename) and os.path.getmtime(filename) > os.path.getmtime(miniature_filename):
                os.unlink(miniature_filename)
                
            # if the image wasn't already resized, resize it
            if not os.path.exists(miniature_filename):
                image = Image.open(filename)
                image.thumbnail([x, y], Image.ANTIALIAS)
                try:
                    image.save(miniature_filename, image.format, quality=100, optimize=1)
                except:
                    image.save(miniature_filename, image.format, quality=100)
            
            output.append(u' <div><a href="%s" target="_blank"><img src="%s" alt="%s" /></a></div> %s ' % \
            (miniature_url, miniature_url, miniature_filename, _('Change:')))
            
        output.append(super(AdminFileWidget, self).render(name, value, attrs))
        return mark_safe(u''.join(output))
    



class PageAdmin(admin.ModelAdmin):
    fields = ('topic', 'pos', 'image')
    list_filter = ('topic__name',)
    ordering = ('pos',)
    inlines = [TextInline, ]
    def formfield_for_dbfield(self, db_field, **kwargs):
        if(db_field.name == 'image'):
            request = kwargs.pop("request", None)
            kwargs['widget'] = AdminImageWidget
            return db_field.formfield(**kwargs)
        return super(PageAdmin, self).formfield_for_dbfield(db_field, **kwargs)
    
admin.site.register(Page, PageAdmin)


class PageInline(admin.TabularInline):
    model = Page
    def formfield_for_dbfield(self, db_field, **kwargs):
        if(db_field.name == 'image'):
            request = kwargs.pop("request", None)
            kwargs['widget'] = AdminImageWidget
            return db_field.formfield(**kwargs)
        return super(PageInline, self).formfield_for_dbfield(db_field, **kwargs)
   
    
class TopicAdmin(admin.ModelAdmin):
    list_display = ('name',)
    inlines = [PageInline, ]
   

    
admin.site.register(Topic, TopicAdmin)

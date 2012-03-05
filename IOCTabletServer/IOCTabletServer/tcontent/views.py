# Create your views here.
from tcontent.models import Topic
from tcontent.models import Page
from tcontent.models import Text
from django.http import HttpResponse

def index(request, topic, lang, page):
    text = Text.objects.get(lang=lang,
                            page=Page.objects.get(pos=page,
                                                  topic=Topic.objects.get(name=topic))).text
    return HttpResponse(text)

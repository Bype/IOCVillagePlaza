from django.conf.urls.defaults import patterns, include, url

# Uncomment the next two lines to enable the admin:
from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    # Examples: 
    url(r'^media/(?P<path>.*)$', 'django.views.static.serve',{'document_root': 'static'}),
    url(r'^title/(?P<topic>\w+)/(?P<lang>\w+)/(?P<page>\d+)/$', 'tcontent.views.title'),
    url(r'^text/(?P<topic>\w+)/(?P<lang>\w+)/(?P<page>\d+)/$', 'tcontent.views.text'),
    url(r'^imageurl/(?P<topic>\w+)/(?P<lang>\w+)/(?P<page>\d+)/$', 'tcontent.views.imageurl'),
    url(r'^image/(?P<topic>\w+)/(?P<lang>\w+)/(?P<page>\d+).png', 'tcontent.views.image'),
    #url(r'^IOCTabletServer/', include('IOCTabletServer.foo.urls')),

    # Uncomment the admin/doc line below to enable admin documentation:
    url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    url(r'^admin/', include(admin.site.urls)),
)

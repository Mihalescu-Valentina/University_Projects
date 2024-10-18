from django.contrib import admin

# Register your models here.
from django.contrib import admin
from .models import Country,HostCity,Venue,Song,Artist,Edition,Ids
# Register your models here.

admin.site.register(Country)
admin.site.register(HostCity)
admin.site.register(Venue)
admin.site.register(Edition)
admin.site.register(Song)
admin.site.register(Artist)
admin.site.register(Ids)
from django.db import models

# Create your models here.
from django.db import models
from datetime import *
from django.core.exceptions import ValidationError

# Create your models here.

class Country(models.Model):
    country_name = models.CharField(max_length=150, unique=True)
    year_of_entrance = models.IntegerField()
    country_capital = models.CharField(max_length=150, unique=True)
    country_hymn = models.CharField(max_length=150)
    quality_factor = models.IntegerField()
    editions = models.ManyToManyField('Edition', through='Ids')

    def __str__(self):
        return self.country_name


class HostCity(models.Model):
    host_city_name = models.CharField(max_length=150, unique=True)
    host_city_population = models.IntegerField()
    host_city_mayor = models.CharField(max_length=150)
    is_capital = models.BooleanField()
    quality_factor = models.IntegerField()

    def __str__(self):
        return self.host_city_name


class Venue(models.Model):
    venue_name = models.CharField(max_length=150)
    venue_adress = models.CharField(max_length=200, unique=True)
    host_city_id = models.ForeignKey(HostCity, related_name='venues', on_delete=models.CASCADE)
    capacity = models.IntegerField()
    rating = models.FloatField()

    def __str__(self):
        return self.venue_name


def validate_year(year):
    if year > 1960 in value:
        return value
    else:
        raise ValidationError("The year of an eurovision ediiton has to be above 1960")


class Edition(models.Model):
    edition_year = models.IntegerField(validators=[validate_year])
    final_date = models.DateField()
    motto = models.CharField(max_length=200)
    venue_id = models.ForeignKey(Venue, related_name='editions', on_delete=models.CASCADE)
    # winner_id = models.ForeignKey(Country, related_name='editions',on_delete=models.CASCADE)
    countries = models.ManyToManyField(Country, through='Ids')


class Artist(models.Model):
    artist_name = models.CharField(max_length=200)
    artist_age = models.IntegerField(default=0)
    country = models.ForeignKey(Country, on_delete=models.CASCADE, related_name='artists')


class Song(models.Model):
    song_name = models.CharField(max_length=200)
    artist_id = models.ForeignKey(Artist, related_name='songs', on_delete=models.CASCADE)
    release_date = models.CharField(max_length=200, default='')
    album_name = models.CharField(max_length=150, default='')


class Ids(models.Model):
    edition = models.ForeignKey(Edition, on_delete=models.CASCADE)
    country = models.ForeignKey(Country, on_delete=models.CASCADE)
    place = models.IntegerField(default=0)
    points = models.IntegerField(default=0)

    def __str__(self):
        return f"{self.country.country_name}- {self.edition.edition_year}"

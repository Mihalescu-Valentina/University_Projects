from django.db import models

# Create your models here.

class Country(models.Model):
    country_name = models.CharField(max_length=150,unique = True)
    year_of_entrance = models.IntegerField()
    country_capital = models.CharField(max_length=150,unique= True)
    quality_factor = models.IntegerField()

    def __str__(self):
        return self.country_name

class HostCity(models.Model):
    host_city_name = models.CharField(max_length=150,unique = True)
    host_city_population = models.IntegerField()
    quality_factor = models.IntegerField()

    def __str__(self):
        return self.host_city_name


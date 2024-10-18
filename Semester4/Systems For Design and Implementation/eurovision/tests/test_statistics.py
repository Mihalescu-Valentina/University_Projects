from django.test import TestCase

# Create your tests here.

from django.test import TestCase
from django.urls import reverse
from rest_framework import status
from rest_framework.test import APIClient
from eurovision.models import Country, HostCity, Edition, Venue, Ids
from eurovision.serializers import EditionSerializer
from django.urls import reverse
from rest_framework import status
from rest_framework.test import APITestCase


class EditionsByAvgQFTestCase(TestCase):
    def setUp(self):
        self.client = APIClient()

        self.hostcity1 = HostCity.objects.create(host_city_name='hc1', host_city_population=200000,
                                                 host_city_mayor='hcm1', is_capital=True, quality_factor=9000)
        self.venue1 = Venue.objects.create(venue_name='vn1', venue_adress='va1', capacity=9870, rating=4.2,
                                           host_city_id=self.hostcity1)

        self.edition1 = Edition.objects.create(edition_year=2022, final_date='2022-05-04', motto='motto1',
                                               venue_id=self.venue1)
        self.country1 = Country.objects.create(country_name="Belgium", country_capital="Bruxelles",
                                               year_of_entrance=2000, quality_factor=2)

        self.country2 = Country.objects.create(country_name="cn1", country_capital="cc1",
                                               year_of_entrance=2002, quality_factor=4)
        self.country3 = Country.objects.create(country_name="cn2", country_capital="cc2",
                                               year_of_entrance=1999, quality_factor=6)
        self.ids1 = Ids.objects.create(edition_id=1, country_id=1, place=4, points=500)

        self.ids2 = Ids.objects.create(edition_id=1, country_id=2, place=10, points=1000)

        self.ids3 = Ids.objects.create(edition_id=1, country_id=3, place=1, points=12000)

        self.hostcity2 = HostCity.objects.create(host_city_name='hc2', host_city_population=800000,
                                                 host_city_mayor='hcm2', is_capital=False, quality_factor=1800)
        self.venue2 = Venue.objects.create(venue_name='vn2', venue_adress='va2', capacity=8000, rating=3.5,
                                           host_city_id=self.hostcity2)
        self.edition2 = Edition.objects.create(edition_year=2008, final_date='2008-03-04', motto='motto2',
                                               venue_id=self.venue2)
        self.country4 = Country.objects.create(country_name="cn3", country_capital="cc3",
                                               year_of_entrance=1999, quality_factor=1)
        self.ids4 = Ids.objects.create(edition_id=2, country_id=4, place=20, points=50)

    def test_get_tutors_by_avg_student_age(self):
        response = self.client.get('/eurovision/edition/by-avg-qf/')

        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 2)

        self.assertEqual(response.data[0]['id'], self.edition1.id)
        self.assertEqual(response.data[0]['edition_year'], self.edition1.edition_year)
        self.assertEqual(response.data[0]['final_date'], self.edition1.final_date)
        self.assertEqual(response.data[0]['venue_id'], 1)
        self.assertEqual(response.data[0]['avg_qf'], 4.0)

        self.assertEqual(response.data[1]['id'], self.edition2.id)
        self.assertEqual(response.data[1]['edition_year'], self.edition2.edition_year)
        self.assertEqual(response.data[1]['final_date'], self.edition2.final_date)
        self.assertEqual(response.data[1]['venue_id'], 2)
        self.assertEqual(response.data[1]['avg_qf'], 1.0)




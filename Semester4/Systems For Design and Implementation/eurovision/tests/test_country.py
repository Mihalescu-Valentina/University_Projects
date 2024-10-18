from django.test import TestCase

import eurovision.models


class CountryModelTestcase(TestCase):
    @classmethod
    def setUpTestData(cls):
        eurovision.models.Country.objects.create(country_name="Belgium", country_capital="Bruxelles", year_of_entrance=2000, quality_factor=12000)

    def test_string_method(self):
        country = eurovision.models.Country.objects.get(country_name="Belgium")
        expected_string = "Belgium"
        self.assertEqual(str(country), expected_string)
import unittest

from utils_functions import Container, my_filter


class TestFilterContainer(unittest.TestCase):
    def setUp(self) -> None:
        self.test = Container()

    def tearDown(self) -> None:
        pass

    def test_filter_container__integers_container__succes(self):
        self.test = my_filter(self.test, lambda x: x != 1)
        self.assertEqual(len(self.test), 0)
        my_list=[1,6,7,8]
        new_list=my_filter(my_list,lambda x: x%2==0)
        self.assertEqual(new_list,[6,8])

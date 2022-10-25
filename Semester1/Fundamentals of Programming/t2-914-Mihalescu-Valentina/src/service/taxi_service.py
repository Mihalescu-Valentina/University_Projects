import random

from src.domain.taxi import Taxi


class ServiceException(Exception):
    pass


class TaxiService:
    def __init__(self, player_repo):
        self.__taxi_repo = player_repo

    @property
    def get_taxis(self):
        return self.__taxi_repo.taxi_list

    def add_taxi(self,taxi):
        self.__taxi_repo.save_taxi(taxi)

    def Manhattan_distance(self, taxi1, taxi2):
        return abs(taxi1[0] - taxi2[0]) + abs(taxi1[1] - taxi2[1])

    def validate_distance(self,taxi1,taxi2):
        if self.Manhattan_distance(taxi1,taxi2)<=5:
            raise ServiceException
        else:
            return self.Manhattan_distance(taxi1,taxi2)

    def generate_taxis(self,nr):
        id = 0
        taxi_init=list(random.randint(0,100) for i in range(2))
        taxi_obj = Taxi(id, taxi_init, 0)
        if taxi_init[0] > taxi_init[1]:
            aux = taxi_init[0]
            taxi_init[0] = taxi_init[1]
            taxi_init[1] = aux
        for i in range(0, nr):
            taxis = list(random.randint(0, 100) for i in range(2))
            if taxis[0] > taxis[1]:
                aux = taxis[0]
                taxis[0] = taxis[1]
                taxis[1] = aux
            id = id + 1
            taxi = Taxi(id, taxis, 0)
            self.add_taxi(taxi)

        print(self.__taxi_repo.taxi_list)

    """
    the function sssigns the Taxi closest to the start point with the ride (using the Manhattan distance).
    The Taxi's total fare is increased by the distance; it also places the Taxi at the end point of the ride 
    params:
    """
    def add_ride(self):
        pass


            # for i in range(0,nr):
            #     if self.validate_distance()
            # if i==0:
            #     list1=taxi_init
            #     list2=taxis
            # else:
            #     list1=taxis
            # if self.validate_distance(taxis[], taxis[i]):
            #    self.add_taxi(taxi)

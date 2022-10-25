
from dataclasses import dataclass


@dataclass
class Taxi:
    id: int
    locations: list
    fare: int

    def __eq__(self, other):
        return self.id == other.id

    def __str__(self):
        return "{0},{1},{2}\n".format(self.id, self.locations, self.fare)

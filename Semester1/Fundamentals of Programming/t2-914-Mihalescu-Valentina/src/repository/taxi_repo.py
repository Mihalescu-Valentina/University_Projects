class RepostoryException(Exception):
    pass

class TaxiRepository:
    def __init__(self):
        self.data=dict()

    def __getitem__(self, item):
        return self.data[item]
    def __len__(self):
        return len(self.data)

    @property
    def taxi_list(self):
        return list(self.data.values())

    def save_taxi(self, taxi):
       self.data[taxi.id] = taxi




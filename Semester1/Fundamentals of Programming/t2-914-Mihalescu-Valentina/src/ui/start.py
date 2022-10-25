import random

from src.domain.taxi import Taxi


class Console:
    def __init__(self, service):
        self.service = service

    def run(self):
        # cmd_dict = {'list': self.list_taxi}
        nr = int(input("Enter the number of operational taxis-integer between 0 and 10"))
        # id=0
        # for i in range(0, nr):
        #     taxis = list(random.randint(0, 100) for i in range(2))
        #     if taxis[0] > taxis[1]:
        #         aux = taxis[0]
        #         taxis[0] = taxis[1]
        #         taxis[1]=aux
        #     id=id+1
        #     taxi=Taxi(id,taxis,0)
        #     self.service.add_taxi(taxi)
        #     print(taxi)
        self.service.generate_taxis(nr)
            # if i>1:
            #   print(self.service.validate_distance(taxis[i-1],taxis[i]))
            #| x1 - x2 | + | y1 - y2 |.
        # while True:
        #     cmd = input("Enter command: ")
        #     if cmd in cmd_dict:
        #         try:
        #             cmd_dict[cmd]()
        #         except RepositoryException as re:
        #             print(re)
        #         except ValueError as ee:
        #             print(ee)
        #         except Exception as exc:
        #             print(exc)
        #     elif cmd == 'h':
        #         self.print_help()
        #     elif cmd == 'exit':
        #         print("Bye.")
        #         return
        #     else:
        #         print("Command not implemented.")

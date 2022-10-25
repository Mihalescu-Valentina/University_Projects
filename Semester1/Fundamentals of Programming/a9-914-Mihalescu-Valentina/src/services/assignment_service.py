import datetime
import random
import time

from src.repository.assignment_repo import AssignmentRepository,AssignmentRepositoryException
from src.domain.assignment import Assignment
class AssignmentService:
    def __init__(self,assignment_repo):
        self.__assignment_repo=assignment_repo

    def add_assignment(self,assignment):
        self.__assignment_repo.save_assignment(assignment)


    def remove_assignment(self,assignment_id):
        self.__assignment_repo.delete_assignment(assignment_id)

    def update_assignment(self,id,description,deadline):
        new_assignment=Assignment(id,description,deadline)
        self.__assignment_repo.update_assignment(id,new_assignment)

    #this function generates 22 random assignments
    def generate_assignments(self):
        descriptions_list=['hard','easy','medium']
        date_start=datetime.datetime(2021,11,23)
        date_end=datetime.datetime(2021,12,31)
        for i in range(1,5):
              new_assignment=Assignment(i,random.choice(descriptions_list),(date_start+(date_end-date_start)*random.random()).replace(minute=random.choice([0,30,59])).strftime("%Y-%m-%d %H:%M"))
              self.__assignment_repo.save_assignment(new_assignment)

    # a getter for the list in the assignment repo which contains the values of the assignments' dictionary
    @property
    def get_assignments(self):
        return self.__assignment_repo.assignments_list

    def __len__(self):
        return len(self.__assignment_repo)

    def assignment_deadline(self,assignment_id):
        if self.__assignment_repo.assignment_deadline(assignment_id) is None:
            raise AssignmentRepositoryException("The assignment with this id does not exist")
        else:
            return self.__assignment_repo.assignment_deadline(assignment_id)


    def find_by_id_assignment(self, assignment_id):
        return self.__assignment_repo.find_by_id_assignment(assignment_id)



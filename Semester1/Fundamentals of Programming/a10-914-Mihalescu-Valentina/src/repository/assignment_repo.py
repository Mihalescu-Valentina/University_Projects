import pickle

from src.domain.assignment import Assignment
from src.domain.validators import AssignmentValidators, Validators
from utils_functions import Container


class AssignmentRepositoryException(Exception):
    pass


class AssignmentRepository:
    def __init__(self):
        self._data = Container()
        self.__assignment_validator = AssignmentValidators
        self.__validators = Validators

    def __getitem__(self, item):
        return self._data[item]

    # @property
    # def assignments_dict(self):
    #     return self.__data

    def delete_assignment(self, assignment_id):
        if assignment_id in self._data:
            del self._data[assignment_id]
        else:
            raise AssignmentRepositoryException("Assignment with Id " + str(assignment_id) + " does not exist in repo")

    def update_assignment(self, id, new_assignment):
        if new_assignment.assignment_id in self._data:
            self._data[new_assignment.assignment_id] = new_assignment

        else:
            raise AssignmentRepositoryException(
                "Assignment with Id " + str(new_assignment.assignment_id) + " does not exist in repo")

    def find_by_id_assignment(self, assignment_id):
        if assignment_id in self._data:
            return self._data[assignment_id]
        return None

    def save_assignment(self, assignment):
        if self.find_by_id_assignment(assignment.assignment_id) is not None:
            raise AssignmentRepositoryException(
                "There's already an assignment with id {0}".format(assignment.assignment_id))
        self.__assignment_validator.check_description(assignment.description)
        self.__assignment_validator.check_date(assignment.deadline)
        self.__validators.check_id(assignment.assignment_id)
        self._data[assignment.assignment_id] = assignment

    @property
    def assignments_list(self):
        return list(self._data.values())

    #def assignment_list_id(self, assignment_id):
        #return list(self.find_by_id_assignment(assignment_id))
    def __len__(self):
        return len(self._data)

    def assignment_deadline(self, assignment_id):
        if self.find_by_id_assignment(assignment_id):
            for assignment in self.assignments_list:
                if assignment.assignment_id == assignment_id:
                    return assignment.deadline
        return None


class AssignmentFileRepository(AssignmentRepository):
    def __init__(self,file_name):
        super().__init__()
        self._file_name = file_name
        self._load_file()

    def _save_file(self):
        f = open(self._file_name, "wt")
        for assignment in self._data.values():
            f.write(
                str(assignment.assignment_id) + ',' + assignment.description + ',' + str(assignment.deadline) + "\n")

        f.close()

    def _load_file(self):
        f = open(self._file_name, "rt")
        for line in f.readlines():
            assignment_id, description, deadline = line.split(maxsplit=3, sep=',')
            self.save_assignment(Assignment(int(assignment_id), description, deadline.rstrip()))
        f.close()

    def save_assignment(self, assignment):
        super(AssignmentFileRepository, self).save_assignment(assignment)
        self._save_file()

    def update_assignment(self, id, new_assignment):
        super(AssignmentFileRepository, self).update_assignment(id, new_assignment)
        self._save_file()

    def delete_assignment(self,assignment_id):
        super(AssignmentFileRepository,self).delete_assignment(assignment_id)
        self._save_file()

class AssignmentBinRepository(AssignmentRepository):
    def __init__(self,file_name):
        super().__init__()
        self._file_name = file_name
        self._load_file()

    def _save_file(self):
        f = open(self._file_name, "wb")
        pickle.dump(self._data,f)
        f.close()

    def _load_file(self):
        f = open(self._file_name, "rb")
        self._data=pickle.load(f)
        f.close()

    def save_assignment(self, assignment):
        super(AssignmentBinRepository, self).save_assignment(assignment)
        self._save_file()

    def update_assignment(self, id, new_assignment):
        super(AssignmentBinRepository, self).update_assignment(id, new_assignment)
        self._save_file()

    def delete_assignment(self,assignment_id):
        super(AssignmentBinRepository,self).delete_assignment(assignment_id)
        self._save_file()




from src.domain import student
from src.domain.student import Student
from src.domain.validators import Validators, StudentValidators
from src.repository.grade_repo import GradeRepository
import pickle


class StudentRepositoryException(Exception):
    pass


class StudentRepository:
    def __init__(self):
        self._data = dict()
        self.__student_validator = StudentValidators
        self.__validators = Validators
        self.__grade_repo = GradeRepository

    # @property
    # def students_dict(self):
    #     return self.__data

    def __getitem__(self, item):
        return self._data[item]

    @property
    def students_list(self):
        return list(self._data.values())

    def delete_student(self, student_id):
        if int(student_id) in self._data:
            del self._data[student_id]
        else:
            raise StudentRepositoryException("Student with Id " + str(student_id) + " does not exist in repo")

    def update_student(self, id, new_student):
        if new_student.student_id in self._data:
            self._data[new_student.student_id] = new_student

        else:
            raise StudentRepositoryException(
                "Student with Id " + str(new_student.student_id) + " does not exist in repo")

    def find_by_id_student(self, student_id):
        if student_id in self._data:
            return self._data[student_id]
        return None

    def student_name(self, student_id):
        if self.find_by_id_student(student_id):
            for student in self.students_list:
                if student.student_id == student_id:
                    return student.name
        return None

    def save(self, student):
        if self.find_by_id_student(student.student_id) is not None:
            raise StudentRepositoryException("There's already a student with id {0}".format(student.student_id))
        self.__validators.check_id(student.student_id)
        self.__student_validator.check_name(student.name)
        self.__student_validator.check_group(student.group)
        self._data[student.student_id] = student

    def __len__(self):
        return len(self._data)


class StudentFileRepository(StudentRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name
        self._load_file()

    # this function saves information to a text file dedicated for a student
    def _save_file(self):
        f = open(self._file_name, "wt")
        for student in self._data.values():
            f.write(str(student.student_id) + ',' + student.name + ',' + str(student.group) + "\n")

        f.close()

    # this function loads data from a text file dedicated to a student into memory
    def _load_file(self):
        f = open(self._file_name, "rt")
        for line in f.readlines():
            student_id, name, group = line.split(maxsplit=3, sep=',')
            self.save(Student(int(student_id), name, group.rstrip()))
        f.close()

    def save(self, student):
        super(StudentFileRepository, self).save(student)
        self._save_file()

    # this function updates a student from the text file
    def update_student(self, id, new_student):
        super(StudentFileRepository, self).update_student(id, new_student)
        self._save_file()

    def delete_student(self, student_id):
        super(StudentFileRepository, self).delete_student(student_id)
        self._save_file()


class StudentBinRepository(StudentRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name
        self._load_file()

    def _save_file(self):
        f = open(self._file_name, "wb")
        pickle.dump(self._data, f)
        f.close()

    def _load_file(self):
        f = open(self._file_name, "rb")
        self._data = pickle.load(f)
        f.close()

    def save(self, student):
        super(StudentBinRepository, self).save(student)
        self._save_file()

    # this function updates the student from a binary file
    def update_student(self, id, new_student):
        super(StudentBinRepository, self).update_student(id, new_student)
        self._save_file()

    def delete_student(self, student_id):
        super(StudentBinRepository, self).delete_student(student_id)
        self._save_file()

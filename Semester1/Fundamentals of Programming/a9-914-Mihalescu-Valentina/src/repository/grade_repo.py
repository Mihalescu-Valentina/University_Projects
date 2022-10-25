import pickle
from datetime import datetime
from random import random

from src.domain.validators import StudentValidators
from src.services.student_service import StudentService

from src.domain.grade import Grade


class StudentRepositoryException(Exception):
    pass


class GradeRepositoryException(Exception):
    pass


class GradeRepositoryGroupException(Exception):
    pass


class AssignmentRepositoryException(Exception):
    pass


class GradeRepository:
    def __init__(self, student_repository, assignment_repo):
        self._data = dict()
        self.__student_repo = student_repository
        self.__assignment_repo = assignment_repo

    # @property
    # def grades_dict(self):
    #     return self.__data

    def __getitem__(self, item):
        return self._data[item]

    def find_by_ids(self, assignment_id, student_id):
        if (assignment_id, student_id) in self._data:
            return self._data[assignment_id, student_id]
        return None

    def find_by_id_student(self, student_id):
        if student_id in self._data:
            return self._data[student_id]
        return None

    def find_by_id_assignment(self, assignment_id):
        if assignment_id in self._data:
            return self._data[assignment_id]
        return None

    @property
    def grades_list(self):
        return list(self._data.values())

    # this function saves a grade in the dictionary grade if all the conditions are met
    def save(self, grade):
        # self.__student_repo.find_by_id_student(int(grade.student_id))
        if self.__student_repo.find_by_id_student(int(grade.student_id)) is None:
            raise StudentRepositoryException("There's no student with id {0}".format(grade.student_id))
        if self.__assignment_repo.find_by_id_assignment(int(grade.assignment_id)) is None:
            raise AssignmentRepositoryException("There's no assignment with id {0}".format(grade.assignment_id))
        if self.find_by_ids(int(grade.assignment_id), int(grade.student_id)) is not None:
            raise GradeRepositoryException(
                "There's already a grade with the student id {1} and assignment id {0}".format(
                    int(grade.assignment_id), int(grade.student_id)))
        self._data[int(grade.assignment_id), int(grade.student_id)] = grade

    def __len__(self):
        return len(self._data)

    def assign_grade(self, grade):
        nr = 0
        grade1 = Grade(grade.assignment_id, grade.student_id, None)
        for elem in self.ungraded_assignments(grade.student_id):
            if elem == str(grade1):
                nr = 1
        if nr == 0:
            raise GradeRepositoryException("This assignment is already graded-is not in the ungraded list")
        self._data[int(grade.assignment_id), int(grade.student_id)] = grade

    def in_dict(self, student_id):
        for grade in self.grades_list:
            if student_id == grade.student_id:
                return True
        return False

    # this function creates a list of ungraded assignments used at option 12
    def ungraded_assignments(self, student_id):
        grades = []
        if self.in_dict(student_id) is True:
            for grade in self.grades_list:
                if int(grade.student_id) == student_id :
                    if grade.grade_value == 'None' or grade.grade_value is None:
                       grades.append(str(grade))

        return grades

    # this function removes all the grades of the student with id: student_id
    def delete_student_grade(self, student_id):
        for grade in self.grades_list:
            if student_id == grade.student_id:
                del self._data[int(grade.assignment_id), int(student_id)]

    def delete_grade(self, assignment_id, student_id):
        del self._data[int(assignment_id), int(student_id)]

    # this function removes all the grades for the assignments with id assignment_id
    def delete_assignment_grade(self, assignment_id):
        for grade in self.grades_list:
            if assignment_id == grade.assignment_id:
                del self._data[int(assignment_id), int(grade.student_id)]

    def print_dict(self):
        print(self._data)

    # this function checks if the id student_id belongs to one of the students
    def availability_list_student(self, student_id, list):
        for id in list:
            if student_id in id:
                return False
        return True

    # the function returns a list with the assignments that are ungraded even though their deadline has passed
    def ungraded_assignment_pass(self):
        grades = []
        for grade in self.grades_list:
            date_time_obj = datetime.strptime(self.__assignment_repo.assignment_deadline(grade.assignment_id),
                                              "%Y-%m-%d %H:%M")
            if self.availability_list_student(grade.student_id,
                                              grades) is True and grade.grade_value is None and date_time_obj < datetime.now():
                li = (grade.student_id, self.__student_repo.student_name(grade.student_id))
                grades.append(li)

        return grades

    def delete_grades_group(self, assignment_id, group_number):
        for grade in self.grades_list:
            if assignment_id == grade.assignment_id and self.__student_repo.find_by_id_student(
                    grade.student_id).group == group_number:
                del self._data[int(assignment_id), int(grade.student_id)]

    def assign_None(self, assignment_id, student_id, grade_val=None):
        grade = Grade(assignment_id, student_id, grade_val)
        self._data[int(grade.assignment_id), int(grade.student_id)] = grade

    # this function assign an assignment with assignment_id to an existent group
    def assign_group_list(self, student_group, assignment_id):
        students = self.__student_repo.students_list
        StudentValidators.check_group(student_group)

        nr = 0
        for student in students:
            if int(student.group) == student_group and self.find_by_ids(int(assignment_id),
                                                                   int(student.student_id)) is None:
                self.save(Grade(assignment_id, student.student_id, None))
                nr = nr + 1
        if nr == 0:
            raise GradeRepositoryException(
                "There is no student in this group,choose another group/all students in this group have already been "
                "given this assignment")

    # self.__grade_repo.grades_dict[student]=Grade(assignment_id,students[student].student_id,None)

#this class is used for working with text files
class GradeFileRepository(GradeRepository):
    def __init__(self, file_name,student_repository, assignment_repository):
        super().__init__(student_repository, assignment_repository)
        self._file_name = file_name
        self._load_file()

    #this method is used for writing data into a file
    def _save_file(self):
        f = open(self._file_name, "wt")
        for grade in self._data.values():
            f.write(str(grade.assignment_id) + ',' + str(grade.student_id) + ',' + str(grade.grade_value) + "\n")

        f.close()

    #this function is used for loading data from the text file
    def _load_file(self):
        f = open(self._file_name, "rt")
        for line in f.readlines():
            assignment_id, student_id, grade_value = line.split(maxsplit=3, sep=',')
            self.save(Grade(int(assignment_id), int(student_id), grade_value.rstrip()))
        f.close()
        pass

    #this function is used for adding a student to the text file
    def save(self, grade):
        super(GradeFileRepository, self).save(grade)
        self._save_file()


    def delete_grade(self, assignment_id, student_id):
        super(GradeFileRepository, self).delete_grade(assignment_id, student_id)
        self._save_file()

    def delete_student_grade(self, student_id):
        super(GradeFileRepository, self).delete_student_grade(student_id)
        self._save_file()

    def delete_assignment_grade(self, assignment_id):
        super(GradeFileRepository, self).delete_assignment_grade(assignment_id)
        self._save_file()

    def assign_group_list(self, student_group, assignment_id):
        super(GradeFileRepository, self).assign_group_list(student_group, assignment_id)
        self._save_file()

    def assign_grade(self, grade):
        super(GradeFileRepository,self).assign_grade(grade)
        self._save_file()


#this repository is used for working with a binary file for the grades
class GradeBinRepository(GradeRepository):
    def __init__(self, file_name,student_repository, assignment_repository):
        super().__init__(student_repository, assignment_repository)
        self._file_name = file_name
        self._load_file()

    #this method writes data into the binary file
    def _save_file(self):
        f = open(self._file_name, "wb")
        pickle.dump(self._data,f)
        f.close()

    #this method loads data from the binary file int the memory
    def _load_file(self):
        f = open(self._file_name, "rb")
        self._data=pickle.load(f)
        f.close()

    #this method is used to add data into the binary file
    def save(self, grade):
        super(GradeBinRepository, self).save(grade)
        self._save_file()

    #this method is used for removing a grade from the binary file
    def delete_grade(self, assignment_id, student_id):
        super(GradeBinRepository, self).delete_grade(assignment_id, student_id)
        self._save_file()

    #this method is used for removing all the grades of a certain student from the grades binary file
    def delete_student_grade(self, student_id):
        super(GradeBinRepository, self).delete_student_grade(student_id)
        self._save_file()

    #this method is used for removing all the grades for a certain assignment
    def delete_assignment_grade(self, assignment_id):
        super(GradeBinRepository, self).delete_assignment_grade(assignment_id)
        self._save_file()

    #this method is used for assigning an assignment to a group of students and writes this data in a binary file
    def assign_group_list(self, student_group, assignment_id):
        super(GradeBinRepository, self).assign_group_list(student_group, assignment_id)
        self._save_file()

    #this method is used for assigning a grade to a student and saving the result in a binary file
    def assign_grade(self, grade):
        super(GradeBinRepository,self).assign_grade(grade)
        self._save_file()



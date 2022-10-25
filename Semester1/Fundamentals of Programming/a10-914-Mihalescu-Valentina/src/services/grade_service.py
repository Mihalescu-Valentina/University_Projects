import random

from src.domain.grade import Grade
from src.repository.assignment_repo import AssignmentRepository, AssignmentRepositoryException
from src.repository.student_repo import StudentRepository
from src.repository.grade_repo import GradeRepository, GradeRepositoryException
from src.services.student_service import StudentService
from src.services.assignment_service import AssignmentService
from src.domain.assignment import Assignment
from src.domain.validators import StudentValidators, GradeValidator, AssignmentValidators, Validators
from src.utils_functions import comb_sort

class GradeService:
    def __init__(self, grade_repo, student_repo, assignment_repo):
        self.__grade_repo = grade_repo
        self.__student_repo = student_repo
        self.__assignment_repo = assignment_repo

    # @property
    # def grades_dict(self):
    #     return self.__grade_repo.grades_dict

    def add_grade(self, grade):
        self.__grade_repo.save(grade)

    def remove_assignment_grade(self, assignment_id):
        self.__grade_repo.delete_assignment_grade(assignment_id)

    def remove_student_grade(self, student_id):
        self.__grade_repo.delete_student_grade(student_id)

    """
    this function assigns an assignment to one student
    """

    def assign_one(self, student_id, assignment_id):
        # if assignment_id in self.__grade_repo.grades_dict==False:
        #     raise Grade_RepositoryException("This assignment has already been assigned")
        # if not self.availability_list(assignment_id):
        #     raise GradeRepositoryException("This assignment has already been assigned")
        new_entry = Grade(assignment_id, student_id, None)
        self.__grade_repo.save(new_entry)

    # a getter for the list in the grades repo which contains the values of the grades' dictionary
    @property
    def get_grades(self):
        return self.__grade_repo.grades_list


    # def assign_group_list(self, student_group, assignment_id):
    #     students = self.__student_repo.students_list
    #     StudentValidators.check_group(student_group)
    #     # if not self.availability_list(assignment_id):
    #     #     raise GradeRepositoryException("This assignment has already been assigned")
    #
    #     nr = 0
    #     for student in students:
    #         if student.group == student_group and self.__grade_repo.find_by_ids(int(assignment_id),
    #                                                                             int(student.student_id)) is None:
    #             self.__grade_repo.save(Grade(assignment_id, student.student_id, None))
    #             nr = nr + 1
    #     if nr == 0:
    #         raise GradeRepositoryException(
    #             "There is no student in this group,choose another group/all students in this group have already been "
    #             "given this assignment")

    # self.__grade_repo.grades_dict[student]=Grade(assignment_id,students[student].student_id,None)

    def assign_group_list(self,student_group,assignment_id):
        return self.__grade_repo.assign_group_list(student_group,assignment_id)



    def availability_list(self, assignment_id):
        for grade in self.__grade_repo.grades_list:
            if assignment_id == grade.assignment_id:
                return False
        return True

    def availability_list_assignment(self, assignment_id):
        for grade in self.__grade_repo.grades_list:
            if assignment_id == grade.assignment_id:
                return True
        return False

    @staticmethod
    def availability_list_student(student_id, list):
        for id in list:
            if id[0] == student_id:
                return False
        return True

    def __len__(self):
        return len(self.__grade_repo)

    def assign_one_grade(self, grade):
        if grade.grade_value is not None:
            GradeValidator.validate_grade_value(int(grade.grade_value))
            GradeValidator.validate_grade(int(grade.grade_value))
        new_entry = Grade(grade.assignment_id, grade.student_id, grade.grade_value)
        if len(self.__grade_repo) == 0:
            raise GradeRepositoryException("There are no assignments assigned")
        if self.__grade_repo.find_by_ids(int(grade.assignment_id), int(grade.student_id)) is None:
            raise GradeRepositoryException(
                "There is no assignment with id {0} assigned for the student with id {1}".format(
                    int(grade.assignment_id), int(grade.student_id)))

        self.__grade_repo.assign_grade(grade)

    def ungraded_assignments(self, student_id):
        if self.__grade_repo.ungraded_assignments(student_id) == []:
            raise GradeRepositoryException("There is no assignment assigned for the student with id {0}".format(
                int(student_id)) + "/" + "All the assignments for this student have already been graded")
        return self.__grade_repo.ungraded_assignments(student_id)

    def list_desc(self, assignment_id):
        # The function creates a list for the students who have assigned the assignment having the id assignment_id
        Validators.check_id(int(assignment_id))
        if self.availability_list_assignment(int(assignment_id)) is False:
            raise AssignmentRepositoryException(
                "This assignment does not exist/This assignment is not assigned to a student")
        l = []
        grades_list = self.__grade_repo.grades_list
        for ids in grades_list:
            if ids.assignment_id == assignment_id:
                s = ids.student_id
                val = ids.grade_value
                if val != None:
                    li = (s, val)
                    l.append(li)
        if l == []:
            raise AssignmentRepositoryException(
                "None of the assignments having the id {0} were graded".format(int(assignment_id)))
        return l

    def average(self, student_id):
        sum = 0.0
        nr = 0
        grades = self.__grade_repo.grades_list
        for grade in grades:
            if grade.student_id == student_id and grade.grade_value is not None:
                sum = sum + float(grade.grade_value)
                nr = nr + 1
        if sum == 0 and nr == 0:
            # raise GradeRepositoryException(
            #     "The students with id {0} has no assignments assigned/has no assignments graded".format(student_id))
            return 0
        return sum / nr

    def list_desc_avg(self):
        l = []
        grades_list = self.__grade_repo.grades_list
        for ids in grades_list:
            s = ids.student_id
            avg = self.average(s)
            if self.availability_list_student(s, l) and avg != 0:
                li = [s, avg]
                l.append(li)
        if l == []:
            raise GradeRepositoryException(
                "None of the assignments were graded")
        return l

    def grades_order(self, assignment_id):
        # The function puts the elements in a descending order
        list_of = self.list_desc(assignment_id)
        #list_of.sort(key=lambda list: list[1], reverse=True)
        list_of=comb_sort(list_of,lambda grade1,grade2: grade1[1]>grade2[1]) #the condition that must be fulfilled
        return list_of

    def grades_order_avg(self):
        list_of = self.list_desc_avg()
        #list_of.sort(key=lambda list: list[1], reverse=True)
        list_of=comb_sort(list_of,lambda grade1,grade2: grade1[1]>grade2[1])
        return list_of

    def ungraded_assignment(self):
        return self.__grade_repo.ungraded_assignment_pass()

    def random_data(self):
        assignments = self.__assignment_repo.assignments_list
        students = self.__student_repo.students_list
        for i in range(22):
            random_assignment = random.choice(assignments)
            random_student = random.choice(students)
            if not self.__grade_repo.find_by_ids(random_assignment.assignment_id, random_student.student_id):
                choices = [round(random.uniform(1, 10), 2), round(random.uniform(6, 9.5), 2), None]
                random_grade = random.choice(choices)
                ungraded_new_assignment = Grade(random_assignment.assignment_id, random_student.student_id,
                                                random_grade)
                self.add_grade(ungraded_new_assignment)

    def delete_grade(self, assignment_id, student_id):
        return self.__grade_repo.delete_grade(assignment_id, student_id)

    def find_by_ids(self, assignment_id, student_id):
        return self.find_by_ids(assignment_id, student_id)

    def delete_grades_group(self, assignment_id, group_number):
        return self.__grade_repo.delete_grades_group(assignment_id, group_number)

    def assign_None(self, assignment_id,student_id,grade_val=None):
            return self.__grade_repo.assign_None(assignment_id,student_id,grade_val)


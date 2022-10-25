from src.domain.assignment import Assignment
from src.domain.student import Student
from src.repository.assignment_repo import AssignmentRepository, AssignmentRepositoryException
from src.repository.student_repo import StudentRepository, StudentRepositoryException
from src.services.student_service import StudentService
from src.services.assignment_service import AssignmentService
from src.services.grade_service import Grade
from src.repository.grade_repo import GradeRepository, GradeRepositoryException
from src.domain.validators import Validators, StudentValidators, AssignmentValidators, GradeValidator
from src.services.undo_redo import UndoService, UndoObject, UndoException


# the class is used for interracting with the user
from utils_functions import my_filter


class Console:
    def __init__(self, student_service, assignment_service, grade_service, undo_service):
        self.__assignment_service = assignment_service
        self.__student_service = student_service
        self.__grade_service = grade_service
        self.__undo_service = undo_service

    @staticmethod
    def display_menu():
        print("Options: ")
        print("1 - display the students")
        print("2 - display the assignments")
        print("3 - add a new student to the dictionary")
        print("4 - add a new assignment to the dictionary")
        print("5 - remove a student")
        print("6-  remove an assignment")
        print("7-  update a student")
        print("8-  update an assignment")
        print("9-  give assignment to student")
        print("10- give assignment to a group ")
        print("11- display grades")
        print("12- grade an assignment")
        print("13-  statistics 1")
        print("14-  statistics 2")
        print("15-  exit the programme")
        print("16-  statistics 3")
        print("17-  undo")
        print("18-  redo")

    def read_input(self):
        self.display_menu()
        # self.__student_service.generate_random_students()
        # self.__assignment_service.generate_assignments()
        # self.__grade_service.random_data()
        while True:
            option = input("Enter option: ").lower().strip()
            try:
                if option == '15':
                    break

                if option == ' ' or option.isdigit() is False:
                    raise KeyError("You have to introduce a number between 1 and 13")

                if int(option) < 1 or int(option) > 18:
                    raise KeyError("You have to introduce a number between 1 and 18")

                if option.isdigit():
                    self.execute_user_command(option)



            except Exception as error_message:
                print(str(error_message))

    def ui_undo(self):
        try:
            self.__undo_service.undo()
            print("Operation successfully undone!")
        except Exception as e:
            print(e)

    def ui_redo(self):
        try:
            self.__undo_service.redo()
            print("Operation successfully redone!")
        except Exception as e:
            print(e)

    # functions used for printing the grades
    def print_grades(self):
        grades = self.__grade_service.get_grades
        for grade in grades:
            print(str(grade))

    def print_students(self):
        students = self.__student_service.get_students
        for student in students:
            print(str(student))

    def print_assignments(self):
        assignments = self.__assignment_service.get_assignments
        for assignment in assignments:
            print(str(assignment))

    def print_statistics1(self, assignment_id):
        statistics1 = self.__grade_service.grades_order(assignment_id)
        for grade in statistics1:
            print("Student id: {0} Grade Value: {1}".format(int(grade[0]), grade[1]))

    def print_statistics2(self):
        statistics2 = self.__grade_service.grades_order_avg()
        for grade in statistics2:
            print("Student id: {0} Average Value: {1}".format(int(grade[0]), grade[1]))

    def print_statistics3(self):
        statistics3 = self.__grade_service.ungraded_assignment()
        for grade in statistics3:
            print("Student id: {0} Name: {1}".format(int(grade[0]), grade[1]))

    def execute_user_command(self, option):


        if int(option) == 1:
            self.print_students()

        elif int(option) == 2:
            self.print_assignments()

        elif int(option) == 3:
            student_id = int(input("Student_id:"))
            student_name = input("Student_name:")
            student_group = int(input("Student_group:"))
            self.__undo_service.register_operation(UndoObject(lambda: self.__student_service.remove_student(student_id),
                                                              lambda: self.__student_service.add_student(
                                                                  Student(student_id, student_name, student_group))))
            try:
                self.__student_service.add_student(Student(student_id, student_name, student_group))
            except StudentRepositoryException as error_message:
                print(str(error_message))



        elif int(option) == 4:
            assignment_id = int(input("Assignment_id:"))
            assignment_description = input("Assignment_description:")
            assignment_deadline = input("Assignment_deadline:")
            self.__undo_service.register_operation(
                UndoObject(lambda: self.__assignment_service.remove_assignment(assignment_id),
                           lambda: self.__assignment_service.add_assignment(
                               Assignment(assignment_id, assignment_description, assignment_deadline))))
            try:
                self.__assignment_service.add_assignment(
                    Assignment(assignment_id, assignment_description, assignment_deadline))
            except AssignmentRepositoryException as error_message:
                print(str(error_message))

        elif int(option) == 5:
            stud_id = int(input("Student_id:"))

            student = self.__student_service.find_by_id_student(stud_id)
            if not student:
                raise StudentRepositoryException("No student with given id")
            grades = list(my_filter(self.__grade_service.get_grades,lambda x: x.student_id == stud_id))

            def undo_function():
                self.__student_service.add_student(student)
                for grade in grades:
                    self.__grade_service.add_grade(grade)

            def redo_function():
                self.__student_service.remove_student(stud_id)
                self.__grade_service.remove_student_grade(stud_id)

            self.__undo_service.register_operation(UndoObject(undo_function, redo_function))

            try:
                self.__student_service.remove_student(int(stud_id))
            except StudentRepositoryException as error_message:
                print(str(error_message))
            try:
                self.__grade_service.remove_student_grade(stud_id)
            except GradeRepositoryException as error_message:
                print(str(error_message))


        elif int(option) == 6:
            assignment_id = int(input("Assignment_id:"))
            assignment = self.__assignment_service.find_by_id_assignment(assignment_id)

            if not assignment:
                raise AssignmentRepositoryException("No assignment with given id")
            grades = list(my_filter(self.__grade_service.get_grades,lambda x: x.assignment_id == assignment_id))

            def undo_function():
                self.__assignment_service.add_assignment(assignment)
                for grade in grades:
                    self.__grade_service.add_grade(grade)

            def redo_function():
                self.__assignment_service.remove_assignment(assignment_id)
                self.__grade_service.remove_assignment_grade(assignment_id)

            self.__undo_service.register_operation(UndoObject(undo_function, redo_function))

            try:
                self.__assignment_service.remove_assignment(assignment_id)
            except AssignmentRepositoryException as error_message:
                print(str(error_message))
            try:
                self.__grade_service.remove_assignment_grade(assignment_id)
            except GradeRepositoryException as error_message:
                print(str(error_message))



        elif int(option) == 7:
            stud_id = int(input("Student_id:"))
            new_student_name = input("New_Student_name:")
            new_student_group = int(input("New_Student_group:"))
            student = self.__student_service.find_by_id_student(stud_id)
            if not student:
                raise StudentRepositoryException("No student with given id")
            self.__undo_service.register_operation(
                UndoObject(
                    lambda: self.__student_service.update_student(student.student_id, student.name, student.group),
                    lambda: self.__student_service.update_student(stud_id, new_student_name, new_student_group))
            )

            try:
                self.__student_service.update_student(stud_id, new_student_name, new_student_group)

            except StudentRepositoryException as error_message:
                print(str(error_message))

        elif int(option) == 8:
            assignment_id = int(input("Assignment_id:"))
            new_assignment_description = input("New_Assignment_description:")
            new_assignment_deadline = input("New_Assignment_deadline:")
            assignment = self.__assignment_service.find_by_id_assignment(assignment_id)
            if not assignment:
                raise AssignmentRepositoryException("No assignment with given id")
            self.__undo_service.register_operation(
                UndoObject(
                    lambda: self.__assignment_service.update_assignment(assignment.assignment_id,
                                                                        assignment.description, assignment.deadline),
                    lambda: self.__assignment_service.update_assignment(assignment_id, new_assignment_description,
                                                                        new_assignment_deadline))
            )

            try:
                self.__assignment_service.update_assignment(assignment_id, new_assignment_description,
                                                            new_assignment_deadline)

            except AssignmentRepositoryException as error_message:
                print(str(error_message))

        elif int(option) == 9:
            stud_id = int(input("Student_id:"))
            assignment_id = int(input("Assignment_id:"))
            self.__undo_service.register_operation(
                UndoObject(
                    lambda: self.__grade_service.delete_grade(assignment_id, stud_id),
                    lambda: self.__grade_service.assign_one(stud_id, assignment_id))
            )

            try:
                self.__grade_service.assign_one(stud_id, assignment_id)

            except GradeRepositoryException as error_message:
                print(str(error_message))

        elif int(option) == 10:
            group_number = int(input("Group number"))
            assignment_id = int(input("Assignment_id:"))

            self.__undo_service.register_operation(
                UndoObject(
                    lambda: self.__grade_service.delete_grades_group(assignment_id, group_number),
                    lambda: self.__grade_service.assign_group_list(group_number, assignment_id)
                ))
            try:
                self.__grade_service.assign_group_list(group_number, assignment_id)
            except GradeRepositoryException as error_message:
                print(str(error_message))


        elif int(option) == 11:
            self.print_grades()


        elif int(option) == 12:
            stud_id = int(input("The id of the student is:"))
            if self.__grade_service.ungraded_assignments(stud_id) != []:
                print("The list of assignments available for grading of the student with id {0} is:".format(stud_id))
                print(str(self.__grade_service.ungraded_assignments(stud_id)))
            else:
                print(str(self.__grade_service.ungraded_assignments(stud_id)))

            if self.__grade_service.ungraded_assignments(stud_id) != []:
                print("Assignment that is graded is:")
                assignment_id = int(input("Choose from the list below"))
                grade_val = int(input("The grade is:"))
                self.__undo_service.register_operation(
                    UndoObject(
                        lambda: self.__grade_service.assign_None(assignment_id, stud_id),
                        lambda: self.__grade_service.assign_one_grade(Grade(assignment_id, stud_id, grade_val))
                    ))
                self.__grade_service.assign_one_grade(Grade(int(assignment_id), int(stud_id), int(grade_val)))


        elif int(option) == 13:
            assignment_id = int(input("Enter a valid assignment:"))
            self.print_statistics1(assignment_id)

        elif int(option) == 14:
            self.print_statistics2()

        elif int(option) == 16:
            if self.__grade_service.ungraded_assignment() == []:
                print("All the assignments have been handed in time/There are no assignments assigned")
            else:
                self.print_statistics3()

        elif int(option) == 17:
            self.ui_undo()

        elif int(option) == 18:
            self.ui_redo()


from src.domain.student import Student
import names
import random
from src.domain.validators import StudentValidators




class StudentService:
    def __init__(self, student_repo):
        self.__student_repo = student_repo


    def add_student(self, student):
        self.__student_repo.save(student)

    #the function generates 22 random students
    def generate_random_students(self):
        for i in range(1, 23):
            new_student = Student(i, names.get_full_name(), random.randint(911, 917))
            self.__student_repo.save(new_student)

    def remove_student(self, student_id):
        self.__student_repo.delete_student(int(student_id))


    def update_student(self, id, name, group):
        StudentValidators()
        new_student = Student(id, name, group)
        self.__student_repo.update_student(id, new_student)

    #a getter for the list in the student repo which contains the values of the students' dictionary
    @property
    def get_students(self):
        return self.__student_repo.students_list

    #returns the length of the dictionary
    def __len__(self):
        return len(self.__student_repo)

    def find_by_id_student(self,student_id):
        return self.__student_repo.find_by_id_student(student_id)


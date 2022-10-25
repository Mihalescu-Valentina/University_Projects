import unittest
from src.domain.student import Student
from src.domain.validators import StudentValidators, Validators, ValidatorException
from src.services.student_service import StudentService
from src.repository.student_repo import StudentRepository, StudentRepositoryException

class TestStudent(unittest.TestCase):
    def setUp(self) -> None:
        unittest.TestCase.setUp(self)
        self.__repo = StudentRepository()
        self.__service = StudentService(self.__repo)

    def tearDown(self):
        unittest.TestCase.tearDown(self)

    def test_entity(self):
        #test creation of class Student in domain
        stud_id=1234
        stud_name="Mihalescu Valentina"
        stud_group=914
        student=Student(stud_id,stud_name,stud_group)
        self.assertEqual(student.student_id,1234)
        self.assertEqual(student.name,"Mihalescu Valentina")
        self.assertEqual(student.group,914)

    #tests for repository:
    def test_student_repo(self):
        student1 = Student(1, "name surname", 914)
        self.assertEqual(len(self.__repo), 0)
        self.__repo.save(student1)
        self.assertEqual(len(self.__repo), 1)
        saved = self.__repo.find_by_id_student(1)
        self.assertEqual(saved, student1)
        self.assertListEqual(self.__repo.students_list, [student1])
        with self.assertRaises(StudentRepositoryException) as context:
            self.__repo.save(student1)
        self.assertEqual("There's already a student with id 1", str(context.exception))
        self.assertEqual(self.__repo[1], student1)

        self.__repo.update_student(1, Student(1, "updated name", 915))
        self.assertEqual(self.__repo.find_by_id_student(1).name, "updated name")
        with self.assertRaises(StudentRepositoryException) as context:
            self.__repo.update_student(3, Student(3, "lala alal", 913))
        self.assertEqual("Student with Id 3 does not exist in repo", str(context.exception))

        self.__repo.delete_student(1)
        self.assertEqual(len(self.__repo), 0)
        with self.assertRaises(StudentRepositoryException) as context:
            self.__repo.delete_student(3)
        self.assertEqual("Student with Id 3 does not exist in repo", str(context.exception))

    def test_student_service(self):
        student1 = Student(1, "name name", 911)
        self.assertEqual(len(self.__service), 0)
        self.__service.add_student(student1)
        self.assertEqual(len(self.__service), 1)
        self.assertListEqual(self.__service.get_students, [student1])

        self.__service.update_student(1, "updated name", 912)
        self.assertEqual(self.__service.get_students[0].name, "updated name")

        self.__service.remove_student(1)
        self.assertEqual(len(self.__service), 0)

        self.__service.generate_random_students()
        self.assertEqual(len(self.__service), 22)

        for i in range(1, 23):
            self.__service.remove_student(i)

    def test_student_validator(self):
        with self.assertRaises(ValidatorException) as context:
            Validators.check_id("sdfsd")
        self.assertEqual("The id must be a positive number", str(context.exception))

        with self.assertRaises(ValidatorException) as context:
            Validators.check_id(0)
        self.assertEqual("The id must be a positive number", str(context.exception))

        with self.assertRaises(ValidatorException) as context:
            StudentValidators.check_group("asd")
        self.assertEqual("The group must be a number between 911 and 917", str(context.exception))

        with self.assertRaises(ValidatorException) as context:
            StudentValidators.check_group(927)
        self.assertEqual("The group must be a number between 911 and 917", str(context.exception))

        with self.assertRaises(ValidatorException) as context:
            StudentValidators.check_name("232 12312")
        self.assertEqual("Enter a surname and a name", str(context.exception))

        with self.assertRaises(ValidatorException) as context:
            StudentValidators.check_name("dsfds")
        self.assertEqual("Enter a name and a surname both strings when adding a student", str(context.exception))











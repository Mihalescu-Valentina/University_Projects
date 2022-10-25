import unittest

from src.domain.assignment import Assignment
from src.domain.grade import Grade
from src.domain.student import Student
from src.domain.validators import GradeValidator, Validators, ValidatorException
from src.repository.assignment_repo import AssignmentRepository
from src.repository.student_repo import StudentRepository
from src.services.grade_service import GradeService
from src.repository.grade_repo import GradeRepository, GradeRepositoryException, StudentRepositoryException, AssignmentRepositoryException


class TestStudent(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        self.__student_repo = StudentRepository()
        self.__assignment_repo = AssignmentRepository()
        self.__repo = GradeRepository(self.__student_repo, self.__assignment_repo)
        self.__service = GradeService(self.__repo, self.__student_repo, self.__assignment_repo)

    def tearDown(self):
        unittest.TestCase.tearDown(self)

    def test_grade_entity(self):
        grade1 = Grade(1, 1, 1)
        self.assertEqual(grade1.assignment_id, 1)
        self.assertEqual(grade1.student_id, 1)
        self.assertEqual(grade1.grade_value, 1)
        self.assertEqual(str(grade1), "Assignment_id: 1, Student_id: 1, Grade_value: 1")
        grade2 = Grade(1, 1, 1)
        self.assertEqual(grade1, grade2)

    def test_grade_repo(self):
        self.__student_repo.save(Student(1, "name name", 914))
        self.__assignment_repo.save_assignment(Assignment(1, "desc", "2021-12-12 23:59"))
        self.__assignment_repo.save_assignment(Assignment(2,"desc2", '2022-01-02 20:30'))
        self.__assignment_repo.save_assignment(Assignment(4,"desc 4","2021-11-04 20:59"))
        grade1 = Grade(1, 1, 1)
        self.assertEqual(len(self.__repo), 0)
        self.__repo.save(grade1)
        self.assertEqual(len(self.__repo), 1)
        saved = self.__repo.find_by_ids(1, 1)
        self.assertEqual(self.__repo[(1, 1)], grade1)
        self.assertEqual(saved, grade1)
        self.assertListEqual(self.__repo.grades_list, [grade1])

        with self.assertRaises(StudentRepositoryException) as context:
            self.__repo.save(Grade(2, 2, 2))
        self.assertEqual("There's no student with id 2", str(context.exception))

        self.assertEqual(self.__student_repo.find_by_id_student(1), Student(1, "name name", 914))
        with self.assertRaises(AssignmentRepositoryException) as context:
            self.__repo.save(Grade(5, 1, 2))
        self.assertEqual("There's no assignment with id 5", str(context.exception))

        with self.assertRaises(GradeRepositoryException) as context:
            self.__repo.save(Grade(1, 1, 1))
        self.assertEqual("There's already a grade with the student id 1 and assignment id 1", str(context.exception))
        self.__repo.save(Grade(2,1,3))
        self.__repo.delete_student_grade(1)
        self.assertEqual(self.__repo.grades_list,[])
        self.__repo.save(Grade(4,1,5))
        self.__repo.delete_assignment_grade(4)
        self.assertEqual(self.__repo.grades_list,[])
        self.__repo.save(Grade(4,1,None))
        self.assertEqual(self.__repo.ungraded_assignment_pass(),[(1, 'name name')])






    def test_grade_service(self):
        self.__student_repo.save(Student(1, "name name", 914))
        self.__student_repo.save(Student(2, "name name", 912))
        self.__student_repo.save(Student(3,"name fgh",916))
        self.__student_repo.save(Student(8,"shd fhf",912))
        self.__assignment_repo.save_assignment(Assignment(1, "desc", "2021-12-12 23:59"))
        self.__assignment_repo.save_assignment(Assignment(2, "desc", "2021-12-12 23:59"))
        self.__assignment_repo.save_assignment(Assignment(5,'desc','2022-01-01 20:20'))
        self.__assignment_repo.save_assignment(Assignment(9, 'descr', '2022-01-08 20:20'))
        self.assertTrue(self.__service.availability_list(1))
        self.assertEqual(len(self.__service), 0)
        with self.assertRaises(GradeRepositoryException) as context:
            self.__service.list_desc_avg()
        self.assertEqual("None of the assignments were graded",str(context.exception))
        self.__service.assign_one(1, 1)
        grade1 = Grade(1, 1, 1)
        # self.__service.add_grade(grade1)
        self.assertEqual(len(self.__service), 1)
        self.assertFalse(self.__service.availability_list(1))
        self.assertListEqual(self.__service.get_grades, [grade1])

        with self.assertRaises(GradeRepositoryException) as context:
            self.__service.assign_one(1, 1)
        self.assertEqual("There's already a grade with the student id {0} and assignment id {1}".format(1,1), str(context.exception))

        with self.assertRaises(GradeRepositoryException) as context:
            self.__service.assign_group_list(914, 1)
        self.assertEqual("There is no student in this group,choose another group/all students in this group have already been given this assignment", str(context.exception))

        with self.assertRaises(GradeRepositoryException) as context:
            self.__service.assign_group_list(911, 2)
        self.assertEqual("There is no student in this group,choose another group/all students in this group have already been given this assignment", str(context.exception))

        self.__service.assign_group_list(914, 2)
        self.assertEqual(len(self.__service), 2)

        self.__service.add_grade(Grade(2, 2, 10))
        self.assertEqual(self.__service.average(2),10.0)
        self.__service.assign_one(2, 5)
        self.__service.assign_one(3, 9)
        self.__service.assign_one(2,9)
        self.__service.assign_one_grade(Grade(5,2,6))
        self.__service.assign_one_grade(Grade(9,3,4))
        self.__service.assign_one_grade(Grade(9,2,5))
        self.assertEqual(self.__service.grades_order_avg(),[[2, 7.0], [3, 4.0]])
        self.assertEqual(self.__service.grades_order(9),[(2,5),(3,4)])
        self.__service.assign_one(2,1)
        self.assertEqual(self.__service.ungraded_assignments(2),['Assignment_id: 1, Student_id: 1, Grade_value: None',
 'Assignment_id: 2, Student_id: 1, Grade_value: None',
 'Assignment_id: 1, Student_id: 2, Grade_value: None'])
        with self.assertRaises(GradeRepositoryException) as context:
            self.__service.assign_one_grade(Grade(8,4,2))
        self.assertEqual("There is no assignment with id 8 assigned for the student with id 4",str(context.exception))



    def test_grade_validator(self):
        with self.assertRaises(ValidatorException) as context:
            GradeValidator.validate_grade_value(11)
        self.assertEqual("Enter a valid grade with value between 1 and 10.", str(context.exception))

        with self.assertRaises(ValidatorException) as context:
            GradeValidator.validate_grade("ssadas")
        self.assertEqual("Enter a valid grade! Grade needs to be an integer.", str(context.exception))





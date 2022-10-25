import unittest
from src.domain.assignment import Assignment
from src.domain.validators import AssignmentValidators, Validators, ValidatorException
from src.repository.assignment_repo import AssignmentRepository, AssignmentRepositoryException, \
    AssignmentFileRepository, AssignmentBinRepository
from src.services.assignment_service import AssignmentService


class TestAssignment(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        self.__repo = AssignmentRepository()
        self.__service = AssignmentService(self.__repo)
        # self.__file_repo=AssignmentFileRepository("assignments1.txt")
        # self.__binary_repo=AssignmentBinRepository("assignments1.bin")

    def tearDown(self):
        unittest.TestCase.tearDown(self)

    def test_assignment_entity(self):
        assignment1 = Assignment(1, "desc", "2021-12-12 23:59")
        self.assertEqual(assignment1.assignment_id, 1)
        self.assertEqual(assignment1.description, "desc")
        self.assertEqual(assignment1.deadline, "2021-12-12 23:59")
        self.assertEqual(str(assignment1), "Assignment_id: 1, Description: desc, Deadline: 2021-12-12 23:59")
        assignment2 = Assignment(1, "desc", "2021-12-12 23:59")
        self.assertEqual(assignment1, assignment2)

    def test_assignment_repo(self):
        assignment1 = Assignment(1, "desc", "2021-12-12 23:59")
        self.assertEqual(len(self.__repo), 0)
        self.__repo.save_assignment(assignment1)
        self.assertEqual(len(self.__repo), 1)
        saved = self.__repo.find_by_id_assignment(1)
        self.assertEqual(saved, assignment1)
        self.assertListEqual(self.__repo.assignments_list, [assignment1])
        with self.assertRaises(AssignmentRepositoryException) as context:
            self.__repo.save_assignment(assignment1)
        self.assertEqual("There's already an assignment with id 1", str(context.exception))
        self.assertEqual(self.__repo[1], assignment1)

        self.__repo.update_assignment(1, Assignment(1, "updated desc", "2021-12-12 23:59"))
        self.assertEqual(self.__repo.find_by_id_assignment(1).description, "updated desc")
        with self.assertRaises(AssignmentRepositoryException) as context:
            self.__repo.update_assignment(3, Assignment(3, "desc", "2021-12-12 23:59"))
        self.assertEqual("Assignment with Id 3 does not exist in repo", str(context.exception))

        self.__repo.delete_assignment(1)
        self.assertEqual(len(self.__repo), 0)
        with self.assertRaises(AssignmentRepositoryException) as context:
            self.__repo.delete_assignment(3)
        self.assertEqual("Assignment with Id 3 does not exist in repo", str(context.exception))
        self.assertEqual(self.__repo.assignment_deadline(1),None)

    # def test_assignment_file_repo(self):
    #    assignment1=Assignment(1, "desc", "2021-12-12 23:59")
    #    self.__file_repo._save_file()
    #    self.__file_repo._load_file()
    #    self.__file_repo.save_assignment(assignment1)
    #    self.assertEqual(len(self.__file_repo),1)



    def test_assignment_service(self):
        assignment1 = Assignment(1, "desc", "2021-12-12 23:59")
        self.assertEqual(len(self.__service), 0)
        self.__service.add_assignment(assignment1)
        self.assertEqual(len(self.__service), 1)
        self.assertListEqual(self.__service.get_assignments, [assignment1])

        self.__service.update_assignment(1, "updated desc", 912)
        self.assertEqual(self.__service.get_assignments[0].description, "updated desc")

        self.__service.remove_assignment(1)
        self.assertEqual(len(self.__service), 0)

        self.__service.generate_assignments()
        self.assertEqual(len(self.__service), 4)

        for i in range(1, 5):
              self.__service.remove_assignment(i)


        self.__repo.save_assignment(assignment1)
        self.assertEqual(self.__service.find_by_id_assignment(1),assignment1)
        # with self.assertRaises(AssignmentRepositoryException) as context:
        #     self.__service.find_by_id_assignment(6)
        # self.assertEqual("The assignment with this id does not exist", str(context.exception))
        self.assertEqual(self.__service.find_by_id_assignment(6),None)
        self.assertEqual(self.__service.assignment_deadline(1),"2021-12-12 23:59")
        with self.assertRaises(AssignmentRepositoryException) as context:
            self.__service.assignment_deadline(3)
        self.assertEqual("The assignment with this id does not exist", str(context.exception))


    def test_assignment_validator(self):
        with self.assertRaises(ValidatorException) as context:
            AssignmentValidators.check_description(123)
        self.assertEqual("Enter a valid description! Description needs to be a string.", str(context.exception))

        with self.assertRaises(ValueError) as context:
            AssignmentValidators.check_date("2021-12-12 ")
        self.assertEqual("Incorrect data format, it should be YYYY-MM-DD HH:MM", str(context.exception))

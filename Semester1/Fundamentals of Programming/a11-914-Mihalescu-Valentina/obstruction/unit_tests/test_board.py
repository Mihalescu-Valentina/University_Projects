import unittest

from obstruction.board.board import Board


class TestStudent(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        self.__board = Board()
        self.__row=self.__board.get_row()
        self.__column=self.__board.get_column()

    def tearDown(self):
        unittest.TestCase.tearDown(self)

    def test_grade_entity(self):
        self.__board.set_row(6)
        self.__board.set_column(6)
        c=self.__board.get_column()
        r=self.__board.get_row()
        self.assertEqual(r,6)
        self.assertEqual(c,6)
        self.__board.create_board()
        self.__board.mark_neighbours(2,3)
        self.assertEqual(self.__board[2][2],'*')
        self.__board[2][1]='*'
        self.assertEqual(self.__board[2][1],'*')
        self.__board[2][1]=' '
        self.__board.unmark_neighbours(2,3)
        self.assertEqual(len(self.__board.available_moves()),36)
        self.assertEqual(self.__board.count_neighbours(1,1),3)






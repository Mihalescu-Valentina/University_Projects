import unittest

from obstruction.board.board import Board
from obstruction.game.ai import Ai
from obstruction.validators.validator import Validator


class TestStudent(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        self.__board = Board()
        self.__validators = Validator(self.__board, self.__board.get_row, self.__board.get_column)
        self.__ai=Ai(self.__board)

    def tearDown(self):
        unittest.TestCase.tearDown(self)

    def test_human_move(self):
        self.__board.set_row(6)
        self.__board.set_column(6)
        self.__board.create_board()
        self.assertEqual(self.__ai.is_winner(),False)
        self.__ai.make_move_player(2,2)
        self.__ai.make_move_player(2,5)
        self.__ai.make_move_player(5,2)
        self.__ai.make_move_player(5,5)
        self.assertEqual(self.__ai.is_winner(),True)

    def test_computer_move(self):
        self.__board.set_row(6)
        self.__board.set_column(6)
        self.__board.create_board()
        self.__ai.make_move_player(4,3)
        self.__ai.make_best_move()
        self.assertEqual(self.__board[0][4],' ')
        self.__ai.clear_board()
        self.assertEqual(self.__board[4][3],' ')
        self.__ai.make_move_player(2,2)
        self.__ai.make_move_player(2,5)
        self.__ai.make_move_player(5,2)
        self.__ai.make_move_player(5,4)
        self.__ai.make_best_move()
        self.assertEqual(self.__board[5][5],'0')




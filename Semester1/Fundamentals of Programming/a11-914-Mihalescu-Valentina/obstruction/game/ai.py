from random import randint

from obstruction.validators.validator import Validator

import numpy as np


class AIException(Exception):
    pass



class Ai:
    def __init__(self, board):
        self.__board = board
        self.__validators = Validator(self.__board, self.__board.get_row, self.__board.get_column)

    #function that cheks if the game was won by checking the length of the available moves list
    def is_winner(self):
        if self.__board.available_moves() == []:
            return True
        return False


    def make_move_player(self, r, c):
        """

        :param r: the row which was chosen by the player
        :param c: the column which was chosen by the player
        :return: it just modifies the board
        """
        self.__validators.validate_move(r, c, 6, 6)
        self.__board[r - 1][c - 1] = 'X'
        self.__board.mark_neighbours(r, c)

    #function that is used for moving the computer randomly
    def make_move_computer(self, nr):
        if self.__board.available_moves() != [] and nr != 1:
            r = self.__board.available_moves()[0][0]
            c = self.__board.available_moves()[0][1]
            self.__validators.validate_move(r, c, 6, 6)
            self.__board[r - 1][c - 1] = 'O'
            self.__board.mark_neighbours(r, c)

        elif nr == 1:
            r = randint(1, 6)
            c = randint(1, 6)
            self.__validators.validate_move(r, c, 6, 6)
            self.__board[r - 1][c - 1] = 'O'
            self.__board.mark_neighbours(r, c)

    def set_column_ai(self, column):
        return self.__board.set_column(column)

    def set_row_ai(self, row):
        return self.__board.set_row(row)

    def create_board_ai(self):
        self.__board.create_board()

    def get_board(self):
        return self.__board.get_board

    def display_board_ai(self):
        self.__board.display_board()

    @staticmethod
    def max_value(a, b):
        if a >= b:
            return a
        else:
            return b

    #the minimax algorithm
    def minimax(self, row,column, depth, maximizing_player):
        """

        :param row: the row of the cell for which the score will be calculated
        :param column: the column of the cell for which the score will be calculated
        :param depth: the depth of the tree
        :param maximizing_player: a bool variable that is true if is the maximizing player's turn and false if is the minimizing players'turn
        :return: the highest score possible for the cell on the row r,column c
        """
        if depth==0: # and self.is_winner() is True:
            return self.evaluate_position(row,column)

        if maximizing_player is True:
            maxeval = -np.inf
            for list in self.__board.available_moves():
                self.__board[list[0] - 1][list[1] - 1] = '0'
                eval = self.minimax(list[0]-1,list[1]-1, depth - 1, False)
                self.__board[list[0] - 1][list[1] - 1] = ' '
                maxeval = self.max_value(maxeval, eval)
            return maxeval

        else:
            mineval = np.inf
            for list in self.__board.available_moves():
                self.__board[list[0]-1][list[1]-1]='0'
                eval = self.minimax(list[0]-1,list[1]-1, depth - 1,True)
                self.__board[list[0]-1][list[1]-1]=' '
                mineval= self.min_value(mineval, eval)
            return mineval

    def evaluate_position(self, r,c):
        return self.__board.count_neighbours(r,c)



    #static method which determine the minimum between 2 integers
    @staticmethod
    def min_value(a, b):
        if a <=b:
            return a
        else:
            return b

    #function that calls the minimax algorithm in order for the computer to make the best move possible
    """
        int bestscore-the greatest score possible initially -infinite
        move-a list which will store the moves coresponding to the bestscore
        list-a list which contains 2 elements,the index of an avaialbe row as well as the column
        score=temporary score 
    """
    def make_best_move(self):

        bestscore=-np.inf
        move=[]
        for list in self.__board.available_moves():
            self.__board[list[0]-1][list[1]-1]='O'
            score=self.minimax(list[0]-1,list[1]-1,2,False)
            self.__board[list[0]-1][list[1]-1]=' '

            if score > bestscore:
                bestscore = score
                move = [list[0]-1,list[1]-1]


            if move!=[]:
               self.__board[move[0]][move[1]]='0'
               self.__board.mark_neighbours(move[0]+1,move[1]+1)

            else:
               self.__board[list[0]-1][list[1]-1] = '0'
               self.__board.mark_neighbours(list[0], list[1])
               break

    #function used for cleaning the board-for tests
    def clear_board(self):
        for i in range(5):
            for j in range(6):
                self.__board[i][j]=' '
        return self.__board
import texttable

from obstruction.validators.validator import Validator


class Board():
    def __init__(self, row=0, column=0):
        self.__row = row
        self.__column = column
        self.__board = []

    def set_row(self, value):
        self.__row = value

    def set_column(self, column):
        self.__column = column

    def get_row(self):
        return self.__row

    def get_column(self):
        return self.__column

    def __len__(self):
        return len(self.__board)

    def get_board(self):
        return self.__board

    #function which uses a library from python in order to display the board in a special table format
    def get_texttable(self):
        table = texttable.Texttable(0)
        for row in self.__board:
            table.add_row(row)
        return table

    #the function which calls the previous one and actually displays the board
    def display_board(self):
        print(self.get_texttable().draw())
        return str(self.__board)

    #this function creates a list of lists containing ' '
    def create_board(self):
        for r in range(self.__row):
            list = []
            for c in range(self.__column):
                list.append('')
            self.__board.append(list)




    #dunder method used for making the board itterable
    def __getitem__(self, item):
        return self.__board[item]

    def __setitem__(self, key, value):
        self.__board[key]=value


    #function which fills the neighbours of the cell on line r column c with '*'; it has 8 cases,
    # each branch of the if being representative for a neighbour
    def mark_neighbours(self, r, c):
        r = r - 1
        c = c - 1

        if r>0 and c>0 and self.__board[r-1][c-1]==' ':
            self.__board[r-1][c-1]='*'

        if r>0 and self.__board[r-1][c]==' ':
            self.__board[r-1][c]='*'

        if r>0 and c<self.__column-1 and self.__board[r-1][c+1]==' ':
            self.__board[r-1][c+1]='*'

        if c>0 and self.__board[r][c-1]==' ':
            self.__board[r][c-1]='*'

        if c>0 and r<self.__row-1 and self.__board[r+1][c-1]==' ':
           self.__board[r+1][c-1]='*'

        if r<self.__row-1 and self.__board[r+1][c]==' ':
           self.__board[r+1][c]='*'

        if r<self.__row-1 and c<self.__column-1 and self.__board[r+1][c+1]==' ':
           self.__board[r+1][c+1]='*'

        if c<self.__column-1 and self.__board[r][c+1]==' ':
          self.__board[r][c+1]='*'

    #function which creates a list called moves which stored lists of 2 elements
    # representing the line and the column of the cells that are empty(available)
    def available_moves(self):
        moves=[]
        for r in range(1,self.__row+1):
            for c in range(1,self.__column+1):
                if self.__board[r-1][c-1]==' ':
                    moves.append([r,c])
        return moves

    #function which counts the number of neighbours of a cell used for implementing
    # the points for the minimax algorithm
    def count_neighbours(self,r,c):
        r = r - 1
        c = c - 1
        nr=0

        if r > 0 and c > 0 and self.__board[r - 1][c - 1] == ' ':
            nr=nr+1

        if r > 0 and self.__board[r - 1][c] == ' ':
            nr=nr+1

        if r > 0 and c < self.__column - 1 and self.__board[r - 1][c + 1] == ' ':
            nr=nr+1

        if c > 0 and self.__board[r][c - 1] == ' ':
            nr=nr+1

        if c > 0 and r < self.__row - 1 and self.__board[r + 1][c - 1] == ' ':
            nr=nr+1

        if r < self.__row - 1 and self.__board[r + 1][c] == ' ':
            nr=nr+1

        if r < self.__row - 1 and c < self.__column - 1 and self.__board[r + 1][c + 1] == ' ':
            nr=nr+1

        if c < self.__column - 1 and self.__board[r][c + 1] == ' ':
            nr=nr+1

        return nr


    #function used for unmarking the neighbours of the cell placed on row r,column c
    def unmark_neighbours(self,r,c):
        r = r - 1
        c = c - 1

        if r > 0 and c > 0 and self.__board[r - 1][c - 1] == '*':
            self.__board[r - 1][c - 1] = ' '

        if r > 0 and self.__board[r - 1][c] == '*':
            self.__board[r - 1][c] = ' '

        if r > 0 and c < self.__column - 1 and self.__board[r - 1][c + 1] == '*':
            self.__board[r - 1][c + 1] = ' '

        if c > 0 and self.__board[r][c - 1] == '*':
            self.__board[r][c - 1] = ' '

        if c > 0 and r < self.__row - 1 and self.__board[r + 1][c - 1] == '*':
            self.__board[r + 1][c - 1] = ' '

        if r < self.__row - 1 and self.__board[r + 1][c] == '*':
            self.__board[r + 1][c] = ' '

        if r < self.__row - 1 and c < self.__column - 1 and self.__board[r + 1][c + 1] == '*':
            self.__board[r + 1][c + 1] = ' '

        if c < self.__column - 1 and self.__board[r][c + 1] == '*':
            self.__board[r][c + 1] = ' '

# board = Board()
# board.set_row(6)
# board.set_column(6)
# board.create_board()
# # print(board.get_board())
# # board.display_board()
# validator=Validator(board.get_board())
#
# board.mark_neighbours(2,4)
# board.mark_neighbours(2,6)
# board[4][0]='X'
# board.display_board()
# board.mark_neighbours(6,1)
# board.mark_neighbours(4,5)
# board.display_board()
#

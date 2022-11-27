class ValidatorException(Exception):
    pass

class Validator:
    def __init__(self,board,row,column):
        self.__board=board


    #function used for validating the input of the user
    #3 cases ar covered-the row and columnd indexes are integers but outside th defined board,the 2 values are not integers
    #+the cell is already filled
    def validate_move(self,r,c,rows,columns):
        if type(r) is not int or type(c) is not int:
            raise ValidatorException("The positions introduced must be integers with values between 1 and 6")

        if r-1<0 or r-1 >= rows or c-1 < 0 or c-1>= columns:
            raise ValidatorException("The row and line position must be integers with values between 1 and 6")

        if self.__board[r-1][c-1]!=' ':
            raise ValidatorException("The cell from line {0} and column {1} is already filled".format(r,c))

        # if r - 1 > 0 and r - 1 < self.__board.__column and c - 1 > 0 and c - 1 < self.__board.__row:
        #      return True

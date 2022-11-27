class Game:
    def __init__(self,game):
        self.__game=game

    def start(self):
        cont = True
        nr=0
        ok=1
        self.__game.set_row_ai(6)
        self.__game.set_column_ai(6)
        self.__game.create_board_ai()

        while cont is True:
             try:
                nr=nr+1
                if ok==1:
                      #self.__game.make_move_computer(nr)
                      self.__game.make_best_move()
                      print("The board after the computer's move is")
                      self.__game.display_board_ai()
                      if self.__game.is_winner() is True:
                         print("The computer has won!")
                         cont=False
                         break

                print("Enter 2 moves corresponding to the position of X: ")
                r=int(input("Enter the index of the line: "))
                c=int(input("Enter the index of the column: "))
                self.__game.make_move_player(r,c)
                print("The board after your move is")
                self.__game.display_board_ai()
                if self.__game.is_winner() is True:
                    print('You won!')
                    cont=False
                    break
                ok=1


             except Exception as error:
                     print(error)
                     ok=0













from obstruction.board.board import Board
from obstruction.game.ai import Ai
from obstruction.game.game import Game

if __name__ == '__main__':
    board=Board()
    ai=Ai(board)
    game=Game(ai)
    game.start()

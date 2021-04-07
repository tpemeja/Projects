# -*- coding: utf-8 -*-
''' This is the famous random player whici (almost) always looses.
'''

import time
import Puissance_4
from random import choice
from playerInterface import *

class myPlayer(PlayerInterface):
    ''' Example of a random player for the go. The only tricky part is to be able to handle
    the internal representation of moves given by legal_moves() and used by push() and
    to translate them to the GO-move strings "A1", ..., "J8", "PASS". Easy!

    '''

    def __init__(self):
        self._board = Puissance_4.Board()
        self._mycolor = None

    def getPlayerName(self):
        return "Random Player"

    def reset(self): #Specific function for data creation
        self.__init__()

    def getPlayerMove(self):
        if self._board.is_game_over():
            print("Referee told me to play but the game is over!")
            return "PASS"
        moves = self._board.legal_moves()
        if (len(moves) > 1):
            move = choice(moves)
        else:
            move = moves[0]
        self._board.push(move)
        return Puissance_4.Board.coord_to_name(move)

    def playOpponentMove(self, move):
        self._board.push(Puissance_4.Board.name_to_coord(move))

    def newGame(self, color):
        self._mycolor = color
        self._opponent = Puissance_4.Board.flip(color)

    def endGame(self, winner):
        if self._mycolor == winner:
            print("I won!!!")
        else:
            print("I lost :(!!")

# -*- coding: utf-8 -*-
import time
import Puissance_4
from random import choice
from playerInterface import *

class myPlayer(PlayerInterface):
    #Play the move to win first
    #Or the move to not lose 
    #And then a random move 

    def __init__(self, seed = 42):
        self._board = Puissance_4.Board()
        self._mycolor = None
        
    def getPlayerName(self):
        return "Random Player"

    def reset(self): 
        self.__init__()

    def getPlayerMove(self):
        assert (not self._board.is_game_over())
        moves = self._board.legal_moves()
        if (len(moves) > 1):
            best_move = None
            for move in moves:
                self._board.push(move)
                if(self._board.is_game_over()):
                    if(self._board._winner == self._mycolor):
                        return Puissance_4.Board.coord_to_name(move)
                    else:
                        best_move = move
                self._board.pop()

            if(best_move != None):
                move = best_move
            else:           
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

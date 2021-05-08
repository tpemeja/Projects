# -*- coding: utf-8 -*-
import time
import Puissance_4_bitboard
from playerInterface import *
import numpy as np

class myPlayer(PlayerInterface):

    def __init__(self,network):
        self._board = Puissance_4_bitboard.Board()
        self._mycolor = None
        self._network = network

    def weights(self):
        return self._network._weights

    def new_weights(self, weights):
        self._network._weights = weights

    def getPlayerName(self):
        return "Genetic Player"

    def reset(self): #Specific function for data creation
        self.__init__(self._network)
        
    def choice(self,legal_moves): #peut être changer choice, vérifié si on met toujours le même joueur devant
        predic = []
        for i in range(len(legal_moves)):
            self._board.push(legal_moves[i])
            if(self._board._gameOver):
                self._board.pop()
                return legal_moves[i]
            X_input = np.array([[[int((val&(1<<(i*6+j)))==(1<<(i*6+j))) for val in self._board._board]
                                                                      for j in range(7)] 
                                                                      for i in range(6)])
            if(self._mycolor == Puissance_4_bitboard.Board._RED):
                predic.append(self._network.predict(np.array([X_input.reshape(-1)])))
            else:
                predic.append(1-self._network.predict(np.array([X_input.reshape(-1)])))
            self._board.pop()
        return legal_moves[predic.index(max(predic))]


    def getPlayerMove(self):
        if self._board.is_game_over():
            print("Referee told me to play but the game is over!")
            return "PASS"
        moves = self._board.legal_moves()
        if (len(moves) > 1):
            move = self.choice(moves)
        else:
            move = moves[0]
        self._board.push(move)

        return Puissance_4_bitboard.Board.coord_to_name(move)

    def playOpponentMove(self, move):
        self._board.push(Puissance_4_bitboard.Board.name_to_coord(move))

    def newGame(self, color):
        self._mycolor = color
        self._opponent = Puissance_4_bitboard.Board.flip(color)

    def endGame(self, winner):
        if self._mycolor == winner:
            print("I won!!!")
        else:
            print("I lost :(!!")

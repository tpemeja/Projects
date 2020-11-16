# -*- coding: utf-8 -*-
''' This is the file you have to modify for the tournament. Your default AI player must be called by this module, in the
myPlayer class.

Right now, this class contaAins the copy of the randomPlayer. But you have to change this!
'''

import time
import Goban
from random import choice
from playerInterface import *
import numpy as np
import statistics
import tensorflow as tf
import tensorflow.keras
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, Activation, Flatten
from tensorflow.keras.layers import Conv1D, Conv2D, BatchNormalization, MaxPooling2D
import tensorflow.keras.optimizers as optimizers
from sklearn.model_selection import train_test_split


def my_metric(y_true,y_pred):
  diff = y_true - y_pred
  return((1-abs(diff))*100)

class myPlayer(PlayerInterface):
    ''' Example of a random player for the go. The only tricky part is to be able to handle
    the internal representation of moves given by legal_moves() and used by push() and
    to translate them to the GO-move strings "A1", ..., "J8", "PASS". Easy!

    '''

    def __init__(self):
        self._board = Goban.Board()
        self._mycolor = None
        self._model = tf.keras.models.load_model('myplayer_model.h5', custom_objects={'my_metric': my_metric})
        self._last_opponent_move = None
        self._last_move = None
        self._turn = 0
        self._timer = 0

    def getPlayerName(self):
        return "RenauldhiGo"

    def playOpponentMove(self, move):
        print("Opponent played ", move) # New here
        # the board needs an internal represetation to push the move.  Not a string
        self._last_opponent_move = move
        self._board.push(Goban.Board.name_to_flat(move))

    def newGame(self, color):
        self._mycolor = color
        self._opponent = Goban.Board.flip(color)

    def endGame(self, winner):
        if self._mycolor == winner:
            if (self._mycolor == 1):
                print("+3 points facilement, merci.")
            else:
                print("Il te faut deux coups d'avance pour gagner peut être ?")
        else:
            print("On apprend peu par la victoire, mais beaucoup par la défaite.")

    def board_to_M(self):
        # Adaptation du board Goban vers un array numpy M compréhensible par
        # notre model
        M = np.zeros((9,9,2))
        for i in range(9):
            for j in range(9):
                val = self._board[i*9+j]
                if(val!=0):
                  M[i][j][val-1]=1
        return M

    def board_eval(self,M):
        # Méthode d'évalutation de plateau
        # On adapte les données pour les fournir en argument à notre model
        # Notre model renvoie toujours la probabilité que le joueur BLACK gagne
        to_predict = []
        for _ in range(4):
            to_predict.append(M)
            to_predict.append(np.flipud(M))
            M=np.rot90(M)

        to_predict=np.array(to_predict).reshape(np.array(to_predict).shape[0],9*9*2)
        list_of_prediction = self._model.predict(to_predict)
        pred=[]
        for j in range(8):
            pred.append(list_of_prediction[j][0])

        return statistics.median(pred)

    def max(self,color,nb_recherche):
        # Méthode pour chercher les meilleurs coups sur le plateau actuel
        # Optimisation pour rechercher ces coups localement par rapport à notre
        # dernier coup et par rapport au dernier coup adverse
        moves = self._board.legal_moves()

        if (len(moves) > (nb_recherche+1) and color == self._mycolor):
            L_tmp = list(set(self.get_local_move(self._last_move,1)) & set(self.get_local_move(self._board.name_to_flat(self._last_opponent_move),1)) & set(moves))
            i = 1
            while(len(L_tmp) < nb_recherche and (i<9)):
                i += 1
                L_tmp = list(set(self.get_local_move(self._last_move,i)) & set(self.get_local_move(self._board.name_to_flat(self._last_opponent_move),i)) & set(moves))
            moves = L_tmp
            moves.append(-1)

        if (len(moves) == 1):
            return [[0,-1]]
        list_of_move = []

        for m in moves[:-1]:
            self._board.push(m)
            M = self.board_to_M()
            self._board.pop()

            prediction = self.board_eval(M)
            # si on est WHITE on inverse la prédiction
            if (color == 2):
              prediction = abs(1-prediction)

            list_of_move.append([prediction,m])
        list_of_move.sort(reverse=True)
        return list_of_move

    def get_local_move(self,move,size):
        # fonction pour obtenir une liste de coups locaux en fct du move en argument
        local_move = []
        (col,lin) = self._board.unflatten(move)
        for i in range(max(0,col-size),min(9,col+size+1),1):
            for j in range(max(0,lin-size),min(9,lin+size+1),1):
                local_move.append(self._board.flatten((i,j)))
        return local_move

    def mini_adv(self,nb_recherche):
        # Méthode qui récupère la liste des meilleurs coups trié par probabilité
        # de gagner décroissante après le coup adverse
        # nb_recherche spécifie le nombre de coups recherchés
        # Pour chaque coup trouvé, on cherche le meilleur coup adverse et on
        # regarde notre probabilité de gagner
        best = 0
        moves = self._board.legal_moves()

        list_of_move = []

        if (len(moves) == 2):
            list_of_move.append([0,moves[0]])
            return list_of_move

        # récupération des meilleurs coups personnels
        best_moves = self.max(self._mycolor,nb_recherche)

        for i in range(min(nb_recherche,len(best_moves))):
            m = best_moves[i][1]
            self._board.push(m)
            # on récupère le meilleur move adverse pour cette config
            best_opp_move = self.max(self._mycolor%2+1,0)[0]
            opp_pred,opp_move = best_opp_move[0], best_opp_move[1]
            self._board.push(opp_move)
            M = self.board_to_M()
            self._board.pop()
            self._board.pop()

            prediction = self.board_eval(M)
            # si on est WHITE
            if (self._mycolor == 2):
              prediction = abs(1-prediction)

            list_of_move.append([prediction,m])
        list_of_move.sort(reverse=True)

        # Si jamais l'adversaire va avoir le dernier coup on passe
        if(len(moves)==3):
          for pred,move in list_of_move:
            self._board.push(move)
            moves_after = self._board.legal_moves()
            self._board.pop()
            if(len(moves)==2):
              list_of_move.remove([pred,move])
        return list_of_move

    def own_choice(self):
        # Méthodes de choix de coup

        start_time = time.time()
        # premier coup scripté si on est BLACK ou WHITE
        if (self._turn == 1):
            if(self._mycolor == 1):
                return self._board.name_to_flat("E5")
            else:
                if (self._board.name_to_flat("E5") in self._board.legal_moves()):
                    return self._board.name_to_flat("E5")
                else:
                    return self._board.name_to_flat("C4")
        # PASS si l'adversaire a passé et qu'on est certain de gagner
        if (self._last_opponent_move == 'PASS'):
          score = self._board.compute_score()
          my_score = score[self._mycolor-1]
          opp_score = score[(self._mycolor)%2]
          if (my_score > opp_score):
            print("Alors étranger, on part sans dire aurevoir ?")
            return -1

        # A partir du deuxième coup, on réfléchit à chaque coup jusqu'à 4 minutes
        if ((self._turn >= 2) and (self._timer < 240)):
            best_move = self.mini_adv(10)[0]
            best,move = best_move[0], best_move[1]

        else:
            if (self._timer < 295):
                best_move = self.max(self._mycolor,10)[0]
                best,move = best_move[0], best_move[1]
            else:
                # Il nous reste 5 secondes on joue purement aléatoirement
                return self._board.legal_moves()[0]
        print("--- %s seconds ---" % (time.time() - start_time))
        return move

    def getPlayerMove(self):
        beg_time = time.time()
        self._turn += 1
        if self._board.is_game_over():
            print("Referee told me to play but the game is over!")
            return "PASS"
        move = self.own_choice()
        self._board.play_move(move)
        self._last_move = move

        # New here: allows to consider internal representations of moves
        print("I am playing ", self._board.move_to_str(move))
        print("My current board :")
        self._board.prettyPrint()
        self._timer += (time.time()-beg_time)
        print("Time used :",self._timer)
        # move is an internal representation. To communicate with the interface I need to change if to a string
        return Goban.Board.flat_to_name(move)

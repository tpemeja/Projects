# on fait jouer deux players random jusqu'au bout
# on stocke la liste des coups
# si le fichier avec toutes cette liste de coup existe alors on fait rien

import Puissance_4
import randomPlayer
import os.path
import json

def write_json(data,filename):
    with open(filename, "w") as f:
        json.dump(data, f, indent = 4)

import json

my_file = r'data_puissance_4.json'

import os.path 
 
# Vérifier si le fichier existe ou non 
if not os.path.isfile(my_file): 
    data = {}
    data['match'] = []
    write_json(data,my_file)

DATA_TO_DO = 1000

with open(my_file) as json_file:
    data = json.load(json_file)

    b = Puissance_4.Board()

    players = []
    player1 = randomPlayer.myPlayer()
    player1.newGame(Puissance_4.Board._RED)
    players.append(player1)

    player2 = randomPlayer.myPlayer()
    player2.newGame(Puissance_4.Board._YELLOW)
    players.append(player2)

    nextplayer = 0
    nextplayercolor = Puissance_4.Board._RED
    nbmoves = 1

    wrongmovefrom = 0

    for numb_data in range(DATA_TO_DO):
        print("Data : ",numb_data+1, "/ ",DATA_TO_DO)
        list_of_board = []
        winner = "DEUCE"
        b.reset()
        player1.reset()
        player2.reset()
        while not b.is_game_over():
            legals = b.legal_moves() 
            otherplayer = (nextplayer + 1) % 2
            othercolor = Puissance_4.Board.flip(nextplayercolor)

            move = players[nextplayer].getPlayerMove() 

            if not Puissance_4.Board.name_to_coord(move) in legals:
                wrongmovefrom = nextplayercolor
                break

            b.push(Puissance_4.Board.name_to_coord(move)) 
            list_of_board.append(b.board_to_numb(b._board))
            players[otherplayer].playOpponentMove(move)

            nextplayer = otherplayer
            nextplayercolor = othercolor

        result = b.result()
        if wrongmovefrom > 0:
            if wrongmovefrom == b._YELLOW:
               winner = "RED"
            elif wrongmovefrom == b._RED:
                winner = "YELLOW"
            else:
                print("ERROR",list_of_moves)
                break
        elif result == "0-1":
            winner = "YELLOW"
        elif result == "1-0":
            winner = "RED"

        new_data = {
                    'board': list_of_board[-1],
                    'winner': winner
                    }
                
        if new_data not in data["match"] :
            data["match"].append(new_data)
            while(list_of_board[:-1] != []):
                list_of_board = list_of_board[:-1]
                new_data = {
                            'board': list_of_board[-1],
                            'winner': winner
                            }
                data["match"].append(new_data)
        else:
            print("Already in dataset")

write_json(data,my_file)


# on fait jouer deux players random jusqu'au bout
# on stocke la liste des coups
# si le fichier avec toutes cette liste de coup existe alors on fait rien
# sinon on ajoute le fichier avec qui a win sous le format : nom fichier = liste des coups et contenu = 1 0 0 suivant si c'est EGALITÉ RED YELLOW
# puis on remonte la liste des coups et s'il existe déjà on augmente de 1 sinon on crée le fichier
# Attention quand c'est le fichier de la partie terminé, on ajoute Over comme ça pas besoin de vérifier de nouveau plus tard et on peut mettre un pourcentage de 100%

import Puissance_4
import randomPlayer
import os.path
import json

def write_json(data,filename):
    with open(filename, "w") as f:
        json.dump(data, f, indent = 4)

import json


my_file = r'my_file4.json'

data = {}
data['match'] = []

write_json(data,my_file)

data_to_do = 1

def save_previous(data,list_of_board):
    if(len(list_of_board)>=1):
        save_previous(data,list_of_board[:-1])
        if os.path.isfile(data_dir+str(list_of_board[-1][0])+" "+str(list_of_board[-1][1])+'.txt'):
            fichier = open(data_dir+str(list_of_board[-1][0])+" "+str(list_of_board[-1][1])+'.txt', "r")
            # print ("File exist")
            old_data = [int(i) for i in (fichier.read()).split()]
            fichier.close()
            data = [old_data[0]+data[0],old_data[1]+data[1],old_data[2]+data[2]]

        fichier = open(data_dir+str(list_of_board[-1][0])+" "+str(list_of_board[-1][1])+'.txt', "w")
        fichier.write(str(data[0])+" "+str(data[1])+" "+str(data[2]))
        fichier.close()

def save_data(data,list_of_board):
    if os.path.isfile(data_dir+str(list_of_board[-1][0])+" "+str(list_of_board[-1][1])+'.txt'):
        print ("File exist -> Do nothing")
    elif (str(list_of_board[-1][0])+" "+str(list_of_board[-1][1])+" "+str(data[0])+" "+str(data[1])+" "+str(data[2])+ " Over") in old_data:
        print ("File exist -> Do nothing")
    else:
        fichier = open(data_dir+str(list_of_board[-1][0])+" "+str(list_of_board[-1][1])+'.txt', "w")
        fichier.write(str(data[0])+" "+str(data[1])+" "+str(data[2])+ " Over")
        fichier.close()
    save_previous(data,list_of_board[:-1])


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

    for numb_data in range(data_to_do):
        print("Data : ",numb_data+1, "/ ",data_to_do)
        list_of_board = []
        winner = "DEUCE"
        b.reset()
        player1.reset()
        player2.reset()
        while not b.is_game_over():
            legals = b.legal_moves() # legal moves are given as internal (flat) coordinates, not A1, A2, ...
            otherplayer = (nextplayer + 1) % 2
            othercolor = Puissance_4.Board.flip(nextplayercolor)

            move = players[nextplayer].getPlayerMove() # The move must be given by "A1", ... "J8" string coordinates (not as an internal move)

            if not Puissance_4.Board.name_to_coord(move) in legals:
                wrongmovefrom = nextplayercolor
                break

            b.push(Puissance_4.Board.name_to_coord(move)) # Here I have to internally flatten the move to be able to check it.
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


write_json(data,my_file)


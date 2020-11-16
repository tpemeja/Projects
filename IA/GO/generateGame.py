''' Sorry no comments :).
'''
import Goban
import importlib
import time
from io import StringIO
import sys
import json


def fileorpackage(name):
    if name.endswith(".py"):
        return name[:-3]
    return name

if len(sys.argv) > 2:
    classNames = [fileorpackage(sys.argv[1]), fileorpackage(sys.argv[2])]
elif len(sys.argv) > 1:
    classNames = [fileorpackage(sys.argv[1]), 'myPlayer']
else:
    classNames = ['myPlayer', 'myPlayer']


player1class = importlib.import_module(classNames[0])

player2class = importlib.import_module(classNames[1])




def playgame(b,nextplayer,nextplayercolor,nbmoves,wrongmovefrom,players):
    L_moves = []
    while not b.is_game_over():
        legals = b.legal_moves()
        nbmoves += 1
        otherplayer = (nextplayer + 1) % 2
        othercolor = Goban.Board.flip(nextplayercolor)

        move = players[nextplayer].getPlayerMove() # The move must be given by "A1", ... "J8" string coordinates (not as an internal move)
        L_moves.append(move)
        if not Goban.Board.name_to_flat(move) in legals:
            print(otherplayer, nextplayer, nextplayercolor)
            print("Problem: illegal move")
            wrongmovefrom = nextplayercolor
            break
        b.push(Goban.Board.name_to_flat(move)) # Here I have to internally flatten the move to be able to check it.
        players[otherplayer].playOpponentMove(move)

        nextplayer = otherplayer
        nextplayercolor = othercolor
    return L_moves


def randomGame():
    players = []
    player1 = player1class.myPlayer()
    player1.newGame(Goban.Board._BLACK)
    players.append(player1)
    player2class = importlib.import_module(classNames[1])
    player2 = player2class.myPlayer()
    player2.newGame(Goban.Board._WHITE)
    players.append(player2)

    json_data = {}
    b = Goban.Board()
    nextplayer = 0
    nextplayercolor = Goban.Board._BLACK
    nbmoves = 1
    wrongmovefrom = 0
    json_data["list_of_moves"] = playgame(b,nextplayer,nextplayercolor,nbmoves,wrongmovefrom,players)
    result = b.result()
    if wrongmovefrom > 0:
        if wrongmovefrom == b._WHITE:
            json_data["winner"] = "black"
        elif wrongmovefrom == b._BLACK:
            json_data["winner"] = "white"
        else:
            print("ERROR")
    elif result == "1-0":
        json_data["winner"] = "white"
    elif result == "0-1":
        json_data["winner"] = "black"
    else:
        return
    with open('data.json','a') as f:
        f.write(json.JSONEncoder().encode(json_data))
        f.write(',')

for i in range(1):
    if (i%50 == 0):
        print("Game",i)
    randomGame()

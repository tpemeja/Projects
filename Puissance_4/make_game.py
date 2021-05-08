import Puissance_4_bitboard

def make_game(red_player, yellow_player,win_p=1,lose_p=0,deuce_p=0.5):

    b = Puissance_4_bitboard.Board()

    players = []
    player1 = red_player
    player1.newGame(Puissance_4_bitboard.Board._RED)
    players.append(player1)

    player2 = yellow_player
    player2.newGame(Puissance_4_bitboard.Board._YELLOW)
    players.append(player2)

    nextplayer = 0
    nextplayercolor = Puissance_4_bitboard.Board._RED
    nbmoves = 1

    wrongmovefrom = 0
    coup = 1
    while not b.is_game_over():
        legals = b.legal_moves() # legal moves are given as internal (flat) coordinates, not A1, A2, ...

        nbmoves += 1
        otherplayer = (nextplayer + 1) % 2
        othercolor = Puissance_4_bitboard.Board.flip(nextplayercolor)
        
        move = players[nextplayer].getPlayerMove() # The move must be given by "A1", ... "J8" string coordinates (not as an internal move)

        if not Puissance_4_bitboard.Board.name_to_coord(move) in legals:
            wrongmovefrom = nextplayercolor
            break
        b.push(Puissance_4_bitboard.Board.name_to_coord(move)) # Here I have to internally flatten the move to be able to check it.
        players[otherplayer].playOpponentMove(move)
    
        nextplayer = otherplayer
        nextplayercolor = othercolor

        coup += 1

    result = b.result()
    if wrongmovefrom > 0:
        if wrongmovefrom == b._YELLOW:
            return [win_p,lose_p]
        elif wrongmovefrom == b._RED:
            return [lose_p,win_p]
        else:
            raise EOFError("IMPOSSIBLE")
    elif result == "0-1":
        return [lose_p,win_p]
    elif result == "1-0":
        return [win_p,lose_p]
    else:
        return [deuce_p,deuce_p]
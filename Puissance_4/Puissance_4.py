'''
Based on the code of the Goban implementation by Laurent SIMON 
'''

import numpy as np
#RED plays first
class Board:
    _BOARDSIZE = (6,7) #Row / Column
    _RED = 1
    _YELLOW = 2
    _EMPTY = 0

    @staticmethod
    def flip(player):
        if player == Board._RED:
            return Board._YELLOW
        return Board._RED

    @staticmethod
    def flip_board(M):
        new_M = np.zeros(Board._BOARDSIZE)
        for i in range(Board._BOARDSIZE[0]):
            for j in range(Board._BOARDSIZE[1]):
                if  M[i][j] == Board._RED:
                    new_M[i][Board._BOARDSIZE[1]-1-j] = Board._RED
                elif M[i][j] == Board._YELLOW:
                    new_M[i][Board._BOARDSIZE[1]-1-j] = Board._YELLOW
        return new_M

    @staticmethod
    def name_to_coord(coord):
        indexLetters = {'A':0, 'B':1, 'C':2, 'D':3, 'E':4, 'F':5, 'G':6}
        col = indexLetters[coord]
        return col

    @staticmethod
    def coord_to_name(coord):
        letterIndex = "ABCDEFG"
        return letterIndex[coord]

    @staticmethod
    def board_to_text(M):
        text = ""
        for i in range(Board._BOARDSIZE[0]):
            text+="|"
            for j in range(Board._BOARDSIZE[1]):
                if(M[i][j]==Board._YELLOW):
                    text+="O"
                elif(M[i][j]==Board._RED):
                    text+="X"
                else:
                    text+="."
                text+="|"
            text+="\n"
        return text

    @staticmethod
    def board_to_numb(M):
        numb = [0,0]
        add_numb = 1
        for i in range(len(M)):
            for j in range(len(M[0])):
                if(M[i][j]==Board._RED):
                    numb[0]+=add_numb
                elif(M[i][j]==Board._YELLOW):
                    numb[1]+=add_numb

                add_numb = add_numb<<1
        return numb

    @staticmethod
    def numb_to_board(L):
        M = np.zeros(Board._BOARDSIZE)
        mask = 1
        for i in range(Board._BOARDSIZE[0]):
            for j in range(Board._BOARDSIZE[1]):
                if(L[0]&mask==mask):
                    M[i][j]=Board._RED
                elif(L[1]&mask==mask):
                    M[i][j]=Board._YELLOW

                mask=mask<<1
        return M

    def __init__(self):
        self._board = np.zeros((Board._BOARDSIZE), dtype='int8')
        self._gameOver = False
        self._turn = 0
        self._winner = self._EMPTY
        self._oldboard = []
        self._nextPlayer = self._RED

    def is_game_over(self):
        ''' Checks if the game is over, ie, if you can still put a stone somewhere'''
        return self._gameOver

    def legal_moves(self):
        return [i for i in range(self._BOARDSIZE[1]) if(self._board[0][i] == self._EMPTY)]

    def reset(self):
        self.__init__()

    def set_winner(self):
        self._winner = self._nextPlayer
        self._gameOver = True

    def check(self, i, j):
        if(self._turn >= 7):
            #ligne
            in_a_row = 0
            for k in range(max(0,j-3),min(self._BOARDSIZE[1],j+4)):
                if(self._board[i][k] == self._nextPlayer):
                    in_a_row += 1
                    if(in_a_row >= 4):
                        self.set_winner()
                        return
                else :
                    in_a_row = 0
            if(in_a_row >= 4):
                self.set_winner()
                return

            #colonne
            in_a_row = 0
            for k in range(max(0,i-3),min(self._BOARDSIZE[0],i+4)):
                if(self._board[k][j] == self._nextPlayer):
                    in_a_row += 1
                    if(in_a_row >= 4):
                        self.set_winner()
                        return
                else :
                    in_a_row = 0
            if(in_a_row >= 4):
                self.set_winner()
                return

            #diag hg-bd
            in_a_row = 0
            for k in range(-3,4):
                if((i+k>=0 and i+k<self._BOARDSIZE[0]) and (j+k>=0 and j+k<self._BOARDSIZE[1])):
                    if(self._board[i+k][j+k] == self._nextPlayer):
                        in_a_row += 1
                        if(in_a_row >= 4):
                            self.set_winner()
                            return
                    else :
                        in_a_row = 0
            if(in_a_row >= 4):
                self.set_winner()
                return

            #diag bg-hd
            in_a_row = 0
            for k in range(-3,4):
                if((i+k>=0 and i+k<self._BOARDSIZE[0]) and (j-k>=0 and j-k<self._BOARDSIZE[1])):
                    if(self._board[i+k][j-k] == self._nextPlayer):
                        in_a_row += 1
                        if(in_a_row >= 4):
                            self.set_winner()
                            return
                    else :
                        in_a_row = 0
            if(in_a_row >= 4):
                self.set_winner()
                return

    def play_move(self, m):
        i = 0
        while(i<=self._BOARDSIZE[0]-2 and self._board[i+1][m] == self._EMPTY):
            i+=1
        self._board[i][m] = self._nextPlayer
        self._turn += 1
        if(self._turn >= self._BOARDSIZE[0]*self._BOARDSIZE[1]):
            self._gameOver = True
        self.check(i,m)
        self._nextPlayer = Board.flip(self._nextPlayer)
        return True

    def push(self, m):
        assert not self._gameOver
        old = np.copy(self._board)
        self._oldboard.append(old)
        return self.play_move(m)

    def pop(self):
        assert not  (self._turn==0)
        self._board = self._oldboard[-1]
        self._turn -= 1
        self._oldboard = self._oldboard[:-1]
        self._gameOver = False
        self._winner = self._EMPTY
        self._nextPlayer = Board.flip(self._nextPlayer)

    def text_to_board(self,text):
        board = np.zeros((Board._BOARDSIZE), dtype='int8')
        for i in range(self._BOARDSIZE[0]):
            for j in range(self._BOARDSIZE[1]):
                board[i][j]=text[i*(2*self._BOARDSIZE[1]+2)+2*j+1]
        return board

    def result(self):
        if self._winner == Board._YELLOW:
            return "0-1"
        elif self._winner == Board._RED:
            return "1-0"
        else:
            return "1/2-1/2"


    def svg(self):

        text_width=20
        nb_cells_height = self._BOARDSIZE[0]
        nb_cells_width  = self._BOARDSIZE[1]
        circle_width = 16
        border = 20
        width = 40

        board ='<svg height="'+str(text_width+border*2+(nb_cells_height-1)*width)+'" '+\
        ' width="'+str(text_width+border*2+(nb_cells_width-1)*width)+'" > '

        # The ABCD... line
        board += '<svg height="'+str(text_width)+'" width="' + str(text_width + border*2+(nb_cells_width-1)*width)+'">'
        letters = "ABCDEFG"
        il = 0
        for i in range(border+text_width-5, text_width-5+border+nb_cells_width*width, width):
            board+= '<text x="'+str(i)+'" y="18" font-size="24" font-color="RED">'+letters[il]+'</text>'
            il += 1
        board += '</svg>'

        # The line numbers
        il = 0
        board += '<svg width="'+str(text_width)+'" height="' + str(text_width + border*2+(nb_cells_width-1)*width)+'">'
        for i in range(border+text_width+7, text_width+7+border+(nb_cells_width-1)*width, width):
            board+= '<text y="'+str(i)+'" x="0" font-size="24" font-color="RED">'+str(6-il)+'</text>'
            il += 1
        board += '</svg>'


        # The board by itself 
        board += ' <svg x="'+str(text_width)+'" y="'+str(text_width)+'" height="' + \
        str(text_width+width*(nb_cells_height-1) + 2*border) + '" width="' + \
        str(text_width+width*(nb_cells_width-1) + 2*border) + '" > ' + \
        '<rect x="0" y="0" width="'+str(width*(nb_cells_width-1)+2*border)+'" height="' + str(width*(nb_cells_height-1)+ 2*border) + '" fill="#1b019b" />'

        position = [(x,self._BOARDSIZE[0]-y) for x in range(self._BOARDSIZE[1]) for y in range(self._BOARDSIZE[0])]
        for (x,y) in position:
            board += '<circle cx="'+str(border+width*x) + \
                '" cy="'+str(border+width*(nb_cells_width-y-1))+'" r="' + str(circle_width) + \
                '" stroke="#333333" stroke-width="3" fill="' + \
                "WHITE" +'" />'

        # The stones
        pieces = [(x,self._BOARDSIZE[0]-y,self._board[y,x]) for x in range(self._BOARDSIZE[1]) for y in range(self._BOARDSIZE[0]) if
                self._board[y,x] != Board._EMPTY]
        for (x,y,c) in pieces:
            board += '<circle cx="'+str(border+width*x) + \
                '" cy="'+str(border+width*(nb_cells_width-y-1))+'" r="' + str(circle_width) + \
                '" stroke="#333333" stroke-width="3" fill="' + \
                ("red" if c==1 else "yellow") +'" />'

        board += '</svg></svg>'
        return board
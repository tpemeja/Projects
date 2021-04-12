class PlayerInterface():

    def getPlayerName(self):
        ''' Must return the name of your AI player.'''
        return "Not Defined"

    def getPlayerMove(self):
        return "PASS"

    def playOpponentMove(self, move):
        pass

    def newGame(self, color):
        pass

    def endGame(self, color):
        pass



import numpy as np
import geneticPlayer
from make_game import make_game
import randomPlayer



def Relu(X):
    X[X<0] = 0
    return X

def Sigmoid(X):
    return 1/(1+np.exp(X))

def Linear(X):
    return X

class Network():
    def __init__(self, networkShape, activations=[Relu,Relu,Relu], mean = 0, std = 1): #Same activation for hidden layer
        self._weights = []
        for i in range(len(networkShape)-1):
            self._weights.append(np.random.normal(mean,std, size = (networkShape[i+1], networkShape[i]+1)))
        self._activations = [activations[0]]+[activations[1]]*(len(networkShape)-2)+[activations[2]]
    
    def predict(self, X_input):
        X = X_input
        for i in range(len(self._weights)):
            X = np.concatenate([np.ones((X.shape[0], 1)), X], axis = 1)
            X = self._activations[i](np.dot(X,np.transpose(self._weights[i])))
        return X
            
#https://github.com/BY571/Genetic-Algorithms-Neural-Network-Optimization/blob/master/Genetic%20Algorithm%20on%20Neural%20Network%20Architecture%20and%20Hyperparameter%20Optimization/Neural%20Network%20Architecture%20and%20Hyperparameter%20Optimization.ipynb
class GeneticAlgorithm:

    @staticmethod
    def score(player, adversary, nb_game = 5, Win = 1, Lose = 0, Deuce = 0.5): 
        score_player, score_adversary = 0, 0 
        for _ in range(nb_game):
            #Game 1 
            score =  make_game(player,adversary,win_p=Win,lose_p=Lose,deuce_p=Deuce)
            score_player += score[0]
            score_adversary += score[1]
            player.reset()
            adversary.reset()
            #Game 2
            score =  make_game(adversary,player,win_p=Win,lose_p=Lose,deuce_p=Deuce)
            score_player += score[1]
            score_adversary += score[0]
            adversary.reset()
            player.reset()
        return score_player, score_adversary

    @staticmethod
    def swap(weights_1, weights_2, i, j, k):
        new_weights_1 = []
        new_weights_2 = []
        for a in range(len(weights_1)):
            if(a < i):
                new_weights_1.append(weights_1[a])
                new_weights_2.append(weights_2[a])
            elif(a > i):
                new_weights_1.append(weights_2[a])
                new_weights_2.append(weights_1[a])
            else: # a == i
                n1 = []
                n2 = []
                for b in range(len(weights_1[i])):
                    if(b < j):
                        n1.append(weights_1[i][b])
                        n2.append(weights_2[i][b])
                    elif(b > j):
                        n1.append(weights_2[i][b])
                        n2.append(weights_1[i][b])
                    else: # b == j
                        nn1 = []
                        nn2 = []
                        for c in range(len(weights_1[i][j])):
                            if(c <= k): # on pourrait mettre strictement mais la possiblement pas de changement
                                nn1.append(weights_1[i][j][c])
                                nn2.append(weights_2[i][j][c])
                            else:
                                nn1.append(weights_2[i][j][c])
                                nn2.append(weights_1[i][j][c])
                        n1.append(nn1)
                        n2.append(nn2)
                new_weights_1.append(n1)
                new_weights_2.append(n2)
        return new_weights_1, new_weights_2

    def __init__(self, population_size = 20,
                network_shape = [84,10,1],
                activations=[Relu,Relu,Relu],
                mean = 0, 
                std = 1,
                generations = 5,
                selected_by_generation = 10,
                mode = "truncated",
                mutation_rate = 0.1,
                mutation_probability = 0.1,
                tournament = "RA",
                nb_game = 3,
                game_point = [1,0,0.5]): 
        assert(population_size >= selected_by_generation)
        assert(network_shape[0] == 84 and network_shape[-1] == 1)
        self._population_size = population_size
        self._generations = generations
        self._nb_selected = selected_by_generation
        self._population = np.array([])
        self._score = []
        self._selection_mode = mode #Possible évolution du mode au fil du temps
        self._network_shape = network_shape
        self._activations = activations
        self._mean = mean
        self._std = std
        self._mutation_rate = mutation_rate
        self._mutation_probability = mutation_probability
        self._adversary = randomPlayer.myPlayer()
        self._tournament = tournament
        self._game_point = game_point
        self._nb_game = nb_game

        #Peut être stocker le nombre de player selectionné en entré ou bien le faire évoluer au fil du temps

    def initialize_population(self):
        self._population = np.array([geneticPlayer.myPlayer(Network(self._network_shape, activations = self._activations, mean = self._mean, std = self._std)) for _ in range(self._population_size)])

    def round_robin_tournament(self):
        self._score = [0]*self._population_size
        for i in range(self._population_size):
            for j in range(i+1, self._population_size):
                if(self._population[i]==self._population[j]):
                    print("what")
                score_i, score_j = self.score(self._population[i],self._population[j], nb_game = 1,
                                        Win = self._game_point[0], Lose = self._game_point[1], Deuce = self._game_point[2])
                self._score[i] += score_i
                self._score[j] += score_j
    
    def random_Agent_tournament(self):
        self._score = [0]*self._population_size
        for i in range(self._population_size):
            self._score[i] = self.score(self._population[i], self._adversary, nb_game = self._nb_game,
                             Win = self._game_point[0], Lose = self._game_point[1], Deuce = self._game_point[2])[0]

    def truncated_selection(self):
        assert (self._score != [])
        L = list(enumerate(self._score))
        L.sort(key = lambda x : x[1])
        return [self._population[best_player[0]] for best_player in L]

    def fitness_proportionate_selection(self):
        assert (self._score != [])
        return self._score/np.sum(self._score)

    def selection(self):
        assert (self._score != [])
        assert (self._nb_selected <= self._population_size)
        if(self._selection_mode == "truncated"):
            player_selection = self.truncated_selection()[-self._nb_selected:]
        elif(self._selection_mode == "fitness"):
            proba = self.fitness_proportionate_selection()
            not_zero = len(proba)-np.count_nonzero(proba == 0)
            if(not_zero >= self._nb_selected):
                player_selection = np.random.choice(self._population, self._nb_selected, replace=False, p=proba)
            else:
                player_selection = np.random.choice(self._population, not_zero, replace=False, p=proba)
                player_selection = np.concatenate((player_selection, np.array([geneticPlayer.myPlayer(Network(self._network_shape, activations = self._activations, mean = self._mean, std = self._std)) for _ in range(self._nb_selected-not_zero)])))
        else:
            EOFError("No selection mode selected")
        return player_selection
    
    def mutation(self, player):
        weights = player.weights()
        for i in range(len(weights)):
            for j in range(len(weights[i])):
                for k in range(len(weights[i][j])):
                    if(np.random.rand() < self._mutation_probability): 
                        weights[i][j][k] += np.random.normal(0,self._mutation_rate)
        player.new_weights(weights)

    def crossingover(self, player_1, player_2):
        weights_1 = player_1.weights()
        weights_2 = player_2.weights()
        i = np.random.randint(len(weights_1)) #modifier les valeurs possibles peut être plus au milieu
        j = np.random.randint(len(weights_1[i]))
        k = np.random.randint(len(weights_1[i][j]))
        new_weights_1, new_weights_2 = self.swap(weights_1, weights_2, i, j, k)
        new_player_1 = geneticPlayer.myPlayer(Network(self._network_shape, activations = self._activations, mean = self._mean, std = self._std))
        new_player_1.new_weights(new_weights_1)
        new_player_2 = geneticPlayer.myPlayer(Network(self._network_shape, activations = self._activations, mean = self._mean, std = self._std))
        new_player_2.new_weights(new_weights_2)
        return new_player_1, new_player_2
    

    def new_generation(self,selection):       
        self._population = selection
        new_population = []
        for _ in range(0,self._population_size-self._nb_selected+1,2):
            player_1 = self._population[np.random.randint(self._nb_selected)]
            player_2 = self._population[np.random.randint(self._nb_selected)] #peut être empecher de prendre le même
            new_player_1, new_player_2 = self.crossingover(player_1, player_2)
            self.mutation(new_player_1)
            self.mutation(new_player_2)
            new_population.append(new_player_1)
            new_population.append(new_player_2)

        self._population = np.concatenate((
                                        self._population,
                                        new_population))[:self._population_size]
 

    def run(self, verbal = False): #peut être nombre de generation
        assert(self._population.size != 0)
        for gen in range(self._generations):
            if(self._tournament == "RR"):
                self.round_robin_tournament()
            elif(self._tournament == "RA"):
               self.random_Agent_tournament()
            else:
                EOFError("Select a correct tournament")

            score_players, score_random = 0, 0
            selection = self.selection()
            for player in selection:
                score_player, score_adversary = self.score(player, self._adversary, nb_game = 5,
                                                 Win = self._game_point[0], Lose = self._game_point[1], Deuce = self._game_point[2])
                score_players += score_player
                score_random += score_adversary
            if(verbal == True):
                print(f"Résultat génération {gen} : {score_players}-{score_random}")
            self.new_generation(selection)
            #print(self._population.size, self._population)
        return score_players,score_random
    
    def best(self, nb_players = 1):
        return self.truncated_selection()[-nb_players:]
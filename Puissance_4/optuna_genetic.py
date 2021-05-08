import myNetwork
import optuna

print("Creating the objective ... ")
class Objective(object):
    def __call__(self, trial):
        # Calculate an objective value by using the extra arguments.
        n_layers = trial.suggest_int("n_layers", 1, 5)
        layers = [84]
        for i in range(n_layers):
            layers.append(trial.suggest_int(str(i), 4, 128))
        layers.append(1)
        population_size  = 50
        generations = 20
        nb_game = 5
        selected_by_generation = trial.suggest_int('Number of players selected', 5, 40)
        mode = trial.suggest_categorical('Selection mode', ['truncated', 'fitness'])
        tournament = trial.suggest_categorical('Tournament', ['RA', 'RR'])
        mutation_rate = trial.suggest_float('Mutation rate', 0, 1)
        mutation_probability = trial.suggest_float('Mutation probability', 0, 1)
        gen = myNetwork.GeneticAlgorithm(population_size = population_size,
                                         network_shape = layers,
                                         selected_by_generation = selected_by_generation    ,
                                         mode = mode,
                                         mutation_rate=mutation_rate,
                                         mutation_probability=mutation_probability,
                                         tournament=tournament)
        gen.initialize_population()
        win, lose = gen.run()
        print(f"Résultat {win}-{lose}")
        return win/(win+lose)
print("Done")

TIMEOUT = 30
NB_TRIALS = 50
STUDY_NAME = "Genetic_4"
#os.system('show databases')  
#os.system('mysql -u root -e "DROP database Genetic_2"')  
STR_PATH = "mysql://root@localhost/"+STUDY_NAME

import os
if os.popen('mysql -u root -e "SHOW DATABASES LIKE \''+STUDY_NAME+'\'"').read()!="":
    print("-------------------------------------")
    print("Study {} loaded".format(STUDY_NAME))
    print("-------------------------------------")
    study = optuna.load_study(study_name=STUDY_NAME, storage=STR_PATH)
    
else:            
    print("-------------------------------------")
    print("New study {} created".format(STUDY_NAME))
    print("-------------------------------------")
    os.system('mysql -u root -e "CREATE DATABASE IF NOT EXISTS "'+STUDY_NAME+'"')
    study = optuna.create_study(study_name=STUDY_NAME,direction="maximize", storage=STR_PATH)


study.optimize(Objective(), n_trials  = NB_TRIALS)

trial = study.best_trial
print("******************************")
print("******************************")
print('Accuracy: {}'.format(trial.value))
print("Best hyperparameters: {}".format(trial.params))

"""
test = GeneticAlgorithm(10,[84,10,1], mutation_rate = 0.1, generations = 50, mode = "fitness")
test.initialize_population()
test.run()
test = myNetwork.GeneticAlgorithm(10,[84,10,1], mutation_probability = 0.1, generations = 10, mode = "fitness")
test.initialize_population()
print(test.run())

Accuracy: 0.7125
Best hyperparameters: {'0': 42, '1': 8, '2': 4, 'Mutation probability': 0.8290492666306407, 'Mutation rate': 0.240972478426479, 'Number of players selected': 8, 'Selection mode': 'fitness', 'Tournament': 'RA', 'n_layers': 3}
"""
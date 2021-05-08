import json
import sys
import os
import numpy as np

''' Data format
{ "train" : {
    "input" : [[Board_RED Board_YELLOW], ...]
    "output" : [[YELLOW_win_percent, RED_win_percent], ...]
    }
}
{ "validation" : {
    "input" : [[Board_RED Board_YELLOW], ...]
    "output" : [[YELLOW_win_percent, RED_win_percent], ...]
    }
}
{ "test" : {
    "input" : [[Board_RED Board_YELLOW], ...]
    "output" : [[YELLOW_win_percent, RED_win_percent], ...]
    }
}
}
'''

def return_index(winner):
    if(winner == "YELLOW"):
        return 0
    elif(winner == "RED"):
        return 1
    else :
        return 2

def load_json(json_file):
    with open(json_file) as f:
        data = json.load(f)['boards']
        return data

def write_json(data,filename):
    with open(filename, "w") as f:
        json.dump(data, f, indent = 4)

my_file = r'board_data_Puissance_4_20.json'
new_file =  r'data_set_Puissance_4_20.json'
my_dir = os.getcwd()+os.path.dirname(__file__)[1:]+"\\"

def write_data_set(filename, new_filename, seed=42, training_ratio=0.75, validation_ratio=0.125):
    data = load_json(filename)
    np.random.seed(seed)
    board_data = {}

    X_all = []
    Y_all = []
    for i in data:
        result = data[i]
        nb_game = result[return_index("YELLOW")] + result[return_index("RED")] + result[return_index("DEUCE")]
        X_all.append(i)
        Y_all.append([result[return_index("YELLOW")]/nb_game , result[return_index("RED")]/nb_game])

    X_all = np.array(X_all)
    Y_all = np.array(Y_all)

    # Permutation
    I_permut = np.random.permutation(len(X_all))
    X_permut = X_all[I_permut]
    Y_permut = Y_all[I_permut]

    # Split
    N1 = int(len(X_permut) * training_ratio)
    N2 = int(len(X_permut) * validation_ratio)
    X_train = X_permut[:N1]
    Y_train = Y_permut[:N1]
    X_val = X_permut[N1:N1+N2]
    Y_val = Y_permut[N1:N1+N2]
    X_test = X_permut[N1+N2:]
    Y_test = Y_permut[N1+N2:]

    board_data['train'] = {
        'input': X_train.tolist(),
        'output': Y_train.tolist()
    }
    board_data['validation'] = {
        'input': X_val.tolist(),
        'output': Y_val.tolist()
    }
    board_data['test'] = {
        'input': X_test.tolist(),
        'output': Y_test.tolist()
    }

    write_json(board_data,new_filename)


list_arg = sys.argv

train_split=0.75
val_split=0.125

seed_selected=42

if("-split" in list_arg):
    ind = list_arg.index("-split")
    split_percent = json.loads(list_arg[ind+1])
    train_split = split_percent[0]
    val_split = split_percent[1]

if("-seed" in list_arg):
    ind = list_arg.index("-seed")
    seed_selected = int(list_arg[ind+1])

write_data_set(my_dir+my_file, my_dir+new_file, seed_selected, train_split, val_split)


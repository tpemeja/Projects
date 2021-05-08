import json
import os

''' Data format
{ "boards" : {
    "Board_RED Board_YELLOW" : [YELLOW_win_nb, RED_win_nb, DEUCE_nb]
    ...
}}
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
        data = json.load(f)['match']
        return data

def write_json(data,filename):
    with open(filename, "w") as f:
        json.dump(data, f, indent = 4)

my_file = r'data_Puissance_4_20.json'
new_file =  r'board_data_Puissance_4_20.json'
my_dir = os.getcwd()+os.path.dirname(__file__)[1:]+"\\"

data = load_json(my_dir+my_file)

n = len(data)
board_data = {}

for i in range(n):
    L = data[i]["board"]
    for j in range(len(L)):
        if ("{} {}".format(data[i]["board"][j][0],data[i]["board"][j][1])) not in board_data:
            val = [0,0,0]
            val[return_index(data[i]["winner"])] = 1
            board_data["{} {}".format(data[i]["board"][j][0],data[i]["board"][j][1])] = val 
        else:
            board_data["{} {}".format(data[i]["board"][j][0],data[i]["board"][j][1])][return_index(data[i]["winner"])] += 1

d = {}
d['boards'] = board_data
write_json(d,my_dir+new_file)
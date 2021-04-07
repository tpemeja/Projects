import json
my_file = r'my_file4.json'

def write_json(data,filename):
    with open(filename, "w") as f:
        json.dump(data, f, indent = 4)

with open(my_file) as json_file:
    data = json.load(json_file)
    list_b = []
    list_w = []
    for d in data["match"]:
        list_b.append(d['board'])
        list_w.append(d['winner'])

    print(list_b,list_w)
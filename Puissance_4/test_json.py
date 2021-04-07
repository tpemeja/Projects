import json

data = {}
data['match'] = []
data['match'].append({
    'board': 1,
    'winner': 'Red'
})
data['match'].append({
    'board': 12,
    'winner': 'Red'
})
data['match'].append({
    'board': 3,
    'winner': 'Yellow'
})
print(data)

test = {
    'board': 14,
    'winner': 'Red'
}


my_file = r'my_file4.json'

def write_json(data,filename):
    with open(filename, "w") as f:
        json.dump(data, f, indent = 4)

write_json(data,my_file)

with open(my_file) as json_file:
    data = json.load(json_file)
    y = {'board': 154,'winner': 'Red'}
    if y not in data["match"] :
        print(data["match"])
        data["match"].append(y)

write_json(data,my_file)
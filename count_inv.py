import sys

assert len(sys.argv) == 2

with open(sys.argv[1], 'r') as file:
    ratings = []
    table = []
    file.readline()
    for line in file:
        ratings = line.split(' ')
        ratings = [int(x) for x in ratings]
        table.append(ratings[1:])

for i in range(10):
    print(table[i])

    

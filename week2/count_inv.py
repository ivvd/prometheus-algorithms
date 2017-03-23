import sys

assert len(sys.argv) == 4

def make_array(arr1, arr2):
    res = [0] * len(arr1)
    for i in range(len(arr1)):
        position = arr1[i] - 1
        value = arr2[i]
        res[position] = value
    return res

def count_inversions(a):
    res = 0
    for i in range(len(a)):
        for j in range(i+1, len(a)):
            if a[i] > a[j]:
                res += 1
    return res

with open(sys.argv[1], 'r') as file:
    ratings = []
    table = []
    file.readline()
    for line in file:
        ratings = line.split(' ')
        ratings = [int(x) for x in ratings]
        table.append(ratings[1:])
    
user1 = int(sys.argv[2]) - 1
user2 = int(sys.argv[3]) - 1

a = table[user1]
b = table[user2]
print(a)
print(b)
c = make_array(a, b)
print(c)
d = count_inversions(c)
print(d)

    

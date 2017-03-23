import sys

stat = {}

def count_sort_ch(A, k, d):
    """ A - input list
        k - maximum value of character in position d
        d - position for sorting
        B - sorted list
    """
    C = [0]*k
    for a in A:
        #print('1:', a)
        if a[d] in stat:
            stat[a[d]] += 1
        else:
            stat[a[d]] = 1
        ind = ord(a[d]) - 97
        C[ind] += 1
    #print('2:', len(C), C)
    sum = 0
    for i, c in enumerate(C):
        C[i] = c + sum
        sum += c
    B = list(A)
    #print('3:', C)
    #print('4:', len(B), B)
    for a in reversed(A):
        ind = ord(a[d]) - 97
        #print('5:', a, ind, C[ind])
        B[C[ind]-1] = a
        C[ind] -= 1
    #print('6:', B)    
    return B

def radix_sort_ch(A, d):
    """ A - input list of another character lists
        d - radix
    """
    for i in reversed(range(d)):
        A = count_sort_ch(A, 26, i)
        print(A[0])
    return A

if len(sys.argv) == 1:
    test = ['hzt','sng','ena','sdt','qds','yif','slt','lpz','cqc','hpo']
elif len(sys.argv) == 2:
    test = []
    with open(sys.argv[1], 'r') as file:
        for line in file:
            test.append(line.replace('\n', ''))
else:
    print('Wrong parameters!')
    exit()

#print(test)
my_dict = []
for s in test:
    l = []
    l.extend(s)
    my_dict.append(l)
#print(my_dict)
sort_dict = radix_sort_ch(my_dict, 3)
#print(sort_dict)

stat_swaped = dict(zip(stat.values(), stat.keys()))
ch = stat_swaped[max(stat_swaped)]
#print(ch)
password = ''.join(sort_dict[0]) + ch + ''.join(sort_dict[-1])
print(password)


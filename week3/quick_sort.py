import sys

k = 0

def find_ref(A, p, r):
    L = r - p + 1
    if L > 2:
        if L % 2:
            m = int(L/2) + p
        else:
            m = int(L/2-1) + p
        a = [A[p], A[r], A[m]]
        #print(a)
        a.sort()
        #print(a, a[1])
        med = a[1]
        i = A.index(med)
    else:
        a = list(A)
        #print(a[p:r+1])
        a.sort()
        #print(a[p:r+1])
        med = a[p]
        i = A.index(med)
    return i

def partition_1(A, p, r):
    x = A[r]
    #print(x)
    i = p - 1
    for j in range(p, r):
        #print(i, j, A)
        if A[j] <= x:
            i += 1
            A[i], A[j] = A[j], A[i]
    A[r], A[i+1] = A[i+1], A[r]
    k = r - p
    return A, i+1, k

def partition_2(A, p, r):
    A[p], A[r] = A[r], A[p]
    x = A[r]
    #print(x)
    i = p - 1
    for j in range(p, r):
        #print(i, j, A)
        if A[j] <= x:
            i += 1
            A[i], A[j] = A[j], A[i]
    A[r], A[i+1] = A[i+1], A[r]
    k = r - p
    return A, i+1, k

def partition_3(A, p, r):
    i = find_ref(A, p, r) 
    #print(i)
    #print(A)
    A[i], A[r] = A[r], A[i]
    #print(A)
    x = A[r]
    #print(x)
    i = p - 1
    for j in range(p, r):
        #print(i, j, A)
        if A[j] <= x:
            i += 1
            A[i], A[j] = A[j], A[i]
    A[r], A[i+1] = A[i+1], A[r]
    k = r - p
    #print(A, '\n')
    return A, i+1, k

def quick_sort(A, p, r, func):
    global k
    #print('p =', p, 'r =', r)
    if p < r:
        A, q, i = func(A, p, r)
        #print('q =', q)
        k += i
        #print('k =', k)
        #print(A)
        A = quick_sort(A, p, q-1, func)
        #print(A)
        A = quick_sort(A, q+1, r, func)
        #print(A)
    return A

assert len(sys.argv) == 2

arr = []

with open(sys.argv[1], 'r') as file:
    file.readline()
    for line in file:
        arr.append(int(line))

print('Method 1')
#print(arr)
arr_temp = list(arr)
quick_sort(arr, 0, len(arr)-1, partition_1)
print(k)

print('\nMethod 2')
arr = list(arr_temp)
k = 0
#print(arr)
quick_sort(arr, 0, len(arr)-1, partition_2)
print(k)

print('\nMethod 3')
arr = list(arr_temp)
k = 0
#print(arr)
quick_sort(arr, 0, len(arr)-1, partition_3)
print(k)

#print('------')
#arr = list(arr_temp)
#arr = [8, 2, 4, 5, 7, 1]
#print(arr, find_ref(arr, 0, len(arr)-1))


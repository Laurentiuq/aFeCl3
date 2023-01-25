# stim ca DFS are mai multe posibile solutii
# pentru a verifica daca un DFS e posibil facem algoritmul sa aleaga intr-un mod specific la fiecare pas
# asadar asociem un numar de ordine corespunzator fiecarui nod in functie de locul in care se afla in permutarea data
# ordonam listele de adiacenta conform ordinelor nodurilor
# DFS alege primul nod nevizitat din lista de adiacenta, deci nodul favorabil noua
# daca in urma DFS nu obtinem o parcurgere egala cu permutarea inseamna ca permutarea nu este un DFS posibil
# Complexitate : O(m + n)
def parser():
    while 1:
        data = list(input().split(' '))
        for number in data:
            if len(number) > 0:
                yield (number)


input_parser = parser()


def get_word():
    global input_parser
    return next(input_parser)


def get_number():
    data = get_word()
    try:
        return int(data)
    except ValueError:
        return float(data)


n = get_number()
m = get_number()
perm = []
orders = [0] * (n + 1)

# Atribuim ordinea nodurilor din permutare
for i in range(n):
    node = get_number()
    perm.append(node)
    orders[node] = i
adjList = {key: [] for key in range(1, n + 1)}


# cream lista de adiacenta si sortam nodurile in fiecare lista in functie de ordinea din permutare
for i in range(m):
    node1 = get_number()
    node2 = get_number()
    if adjList.get(node1):
        adjList[node1].append(node2)
    else:
        adjList[node1] = [node2]
    if adjList.get(node2):
        adjList[node2].append(node1)
    else:
        adjList[node2] = [node1]

for k in adjList:
    try:
        adjList[k] = sorted(adjList[k], key=lambda x: orders[x])
    except:
        ""

import sys
sys.setrecursionlimit(100000)
visited = [0] * (n + 1)
dfsPerm = []

# DFS
def DFS(node):
    dfsPerm.append(node)
    visited[node] = 1
    for nextNode in adjList[node]:
        if visited[nextNode] == 0:
            DFS(nextNode)

DFS(1)

# Daca dupa DFS pe lista de adiacenta ordonata obtinem permutarea inseamna ca aceasta este posibila

if dfsPerm == perm:
    print(1)
else:
    print(0)



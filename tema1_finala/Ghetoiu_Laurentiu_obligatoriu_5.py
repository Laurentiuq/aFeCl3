
# BFS pentru care punctele de control sunt puncte de start
# si compara in fiecare BFS care punct de control are distanta mai mica

# Complexitate O(n^2 + n*m) - daca toate nodurile sunt puncte de control

import sys


f = open('graf.in')
n, m = [int(x) for x in f.readline().split()]
adjList = {key: [] for key in [x for x in range(1, n + 1)]}

for i in range(m):
    n1, n2 = [int(x) for x in f.readline().split()]
    adjList[n1].append(n2)
    adjList[n2].append(n1)

controlP = [int(x) for x in f.readline().split()]
# print(controlP)
# print(adjList)
f.close()


# distantele finale
distFin = [sys.maxsize] * (n+1)

def BFS(sNode):
    dist = [sys.maxsize] * (n+1)
    q = [sNode]
    dist[sNode] = 0
    distFin[sNode] = 0  # daca nodul este punct de control distanta e 0
    while len(q) > 0:
        cn = q.pop(0)  # nodul curent
        for el in adjList[cn]:
            if dist[el] == sys.maxsize:
                q.append(el)
                dist[el] = 1 + dist[cn]
                # compara daca distanta e mai mica decat distanta gasita in
                # alte BFS-uri
                if dist[el] < distFin[el]:
                    distFin[el] = dist[el]
    return dist


# BFS pentru fiecare punct de contorl
for pct in controlP:
    BFS(pct)
print(distFin)
out = open('graf.out', 'a')
for el in distFin[1:]:
    out.write(f"{el} ")


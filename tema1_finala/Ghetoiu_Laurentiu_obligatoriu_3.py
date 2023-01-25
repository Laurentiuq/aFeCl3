# Programul foloseste sortarea topologica:
# Se foloseste DFS si la finalul unei recursii(dupa ce se apeleaza si executa DFS pentru vecinii nevizitati) se adauga
# intr-o lista nodul din care a fost apelat DFS(nodul 'parinte'), la final lista se inverseaza

# Lista de adiacenta adauga muchii astfel:
# pentru [1, 0] (pentru a urma cursul 1 trebuie urmat cursul 0 prima data) - muchie 0 -> 1
# Complexitate: O(n + m)

# a)


numCourses = 4
prerequisites = [[1,0],[2,0],[3,1],[3,2]]
class Solution:
    def findOrder(self, numCourses: int, prerequisites):

        # lista de adiacenta adauga muchii astfel:
        # pentru [1, 0] (pentru a urma cursul 1 trebuie urmat cursul 0 prima data) - muchie 0 -> 1
        adjList = {key: [] for key in range(0, numCourses + 1)}
        for el in prerequisites:
            if adjList.get(el[1]):
                adjList[el[1]].append(el[0])
            else:
                adjList[el[1]] = [el[0]]

        print(adjList)

        visited = [0] * numCourses
        topSort = []  # lista in care o sa fie retinuta sortarea topologica

        # DFS, adaugand nodul curent dupa ce apelam recursiv pentru totate nodurile incidente

        def DFS(node):
            visited[node] = 1
            for n in adjList[node]:
                if not visited[n]:
                    DFS(n)
            topSort.append(node)

        for n in range(numCourses):
            if not visited[n]:
                DFS(n)

        topSort.reverse()

        topOrd = dict()  # ordinea din sortarea topologica a nodurilor
        for i in range(len(topSort)):
            topOrd[topSort[i]] = i

        print(topSort)
        # daca un nod din sortarea topologica e situat inaintea parintelui sau => circuit in graf

        for n in range(numCourses):
            for c in adjList[n]:
                if topOrd[c] <= topOrd[n]:
                    return []

        return topSort


# b)

numCourses = 4
prerequisites = [[1, 0], [2, 1], [3, 2], [1, 3]]

# Problema se reduce la afisa un circuit din graf si care respecta ordinea
# folosind sortarea topologica, daca graful nu este un DAG, aceasta nu e posibila dar ne ofera ordinea corecta


class Solution1:
    def findOrder(self, numCourses: int, prerequisites):

        # lista de adiacenta adauga muchii astfel:
        # pentru [1, 0] (pentru a urma cursul 1 trebuie urmat cursul 0 prima data) - muchie 0 -> 1
        adjList = {key: [] for key in range(0, numCourses + 1)}
        for el in prerequisites:
            if adjList.get(el[1]):
                adjList[el[1]].append(el[0])
            else:
                adjList[el[1]] = [el[0]]


        visited = [0] * numCourses
        topSort = []  # lista in care o sa fie retinuta sortarea topologica

        # DFS, adaugand nodul curent dupa ce apelam recursiv pentru totate nodurile incidente

        def DFS(node):
            visited[node] = 1
            for n in adjList[node]:
                if not visited[n]:
                    DFS(n)
            topSort.append(node)

        for n in range(numCourses):
            if not visited[n]:
                DFS(n)

        topSort.reverse()

        topOrd = dict()  # ordinea din sortarea topologica a nodurilor
        for i in range(len(topSort)):
            topOrd[topSort[i]] = i

        # daca un nod din sortarea topologica e situat inaintea parintelui sau => circuit in graf

        # afisam nodurile care formeaza primul circuit in graf daca acesta exista
        for i in range(numCourses):
            currentNode = topSort[i]
            for c in adjList[currentNode]:
                # daca ordinea unui vecin al lui currentNode e mai mica decat ordinea lui currentNode in sortare
                if topOrd[c] <= topOrd[currentNode]:
                    sN = topSort.index(c)  # indexul nodului de la care incepe circuitul si inchide circuitul
                    topSort.insert(i + 1, topSort[sN])  # pentru afisare
                    sol = topSort[topSort.index(c):i + 2] # index(c)-incepe circuitul, i-finalizarea circuitului
                    # (i nodul de la care se intoarce spre c)
                    sol.reverse()  # pentru a respecta conditia c(i) inainte de c(i-1)
                    return sol

        return []


print(Solution1().findOrder(numCourses, prerequisites))
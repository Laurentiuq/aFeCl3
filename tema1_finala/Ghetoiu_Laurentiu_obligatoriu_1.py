# a)

# Programul testeaza daca graful este bipartit folosind bicolorarea.
# Persoanele care nu se inteleg sunt transformate in noduri cu muchie intre ele
# Se atribuie o culoare nodului sursa, iar apoi o alta culoare vecinilor
# Folosind alternant cele doua culori se parcurge tot graful si daca
# la un moment dat se gasesc vecini noduri de aceeasi culoare inseamna ca graful nu este bipartit
# Complexitate = complexitate BFS = O(m + n), m - numarul de muchii, n - numarul de varfuri

n = 4
dislikes = [[1, 2], [1, 3], [2, 4]]


# a)

# Programul testeaza daca graful este bipartit folosind bicolorarea.
# Persoanele care nu se inteleg sunt transformate in noduri cu muchie intre ele
# Se atribuie o culoare nodului sursa, iar apoi o alta culoare vecinilor
# Folosind alternant cele doua culori se parcurge tot graful si daca
# la un moment dat se gasesc vecini noduri de aceeasi culoare inseamna ca graful nu este bipartit
# Complexitate = complexitate BFS = O(m + n), m - numarul de muchii, n - numarul de varfuri

class Solution:
    # crearea listei de adiacenta
    def possibleBipartition(self, n: int, dislikes) -> bool:
        adjList = {key: [] for key in range(1, n + 1)}
        for el in dislikes:
            adjList[el[0]].append(el[1])
            adjList[el[1]].append(el[0])

        # print(adjList)
        colors = [-1] * (n + 1)

        def BFS(self, sNode):
            for i in range(1, n + 1):
                # daca graful nu e conex, pentru fiecare nou nod sursa atribuim o culoare(0)
                if colors[i] == -1:
                    colors[i] = 0
                    q = [(i, i)]
                    while len(q) > 0:
                        pc = q.pop(0)
                        for el in adjList[pc[1]]:
                            # daca vecinul nu este colorat ii atribuim culoarea opusa parintelui
                            if colors[el] == -1:
                                colors[el] = not colors[pc[1]]
                                # adaugam in coada perechi (tata, fiu)
                                q.append((pc[1], el))
                            # daca vecinul este colorat si are aceeasi culoare
                            # cu nodul din care provine nu este posibila bicolorarea
                            elif colors[el] == colors[pc[1]]:
                                return False
            return True

        return BFS(self, 1)


print(Solution().possibleBipartition(n, dislikes))


# b)


# Spre deosebire de mai sus adaugam in doua liste nodurile dupa culoare:
# o lista cu nodurile cu 0 si o lista cele cu 1
class Solution:

    def possibleBipartition(self, n: int, dislikes):
        adjList = {key: [] for key in range(1, n + 1)}
        for el in dislikes:
            if adjList.get(el[0]):
                adjList[el[0]].append(el[1])
            else:
                adjList[el[0]] = [el[1]]
            if adjList.get(el[1]):
                adjList[el[1]].append(el[0])
            else:
                adjList[el[1]] = [el[0]]

        # print(adjList)
        colors = [-1] * (n + 1)

        def BFS(self, sNode):

            possibleList = [[], []]
            for i in range(1, n + 1):
                if colors[i] == -1:
                    colors[i] = 0
                    possibleList[colors[i]].append(i)
                    q = [(i, i)]
                    while len(q) > 0:
                        # print(q)
                        pc = q.pop(0)
                        for el in adjList[pc[1]]:
                            if colors[el] == -1:
                                colors[el] = not colors[pc[1]]
                                possibleList[colors[el]].append(el)
                                q.append((pc[1], el))
                            elif colors[el] == colors[pc[1]]:
                                return "Nu este posibila o impartire"
            return possibleList

        return BFS(self, 1)


print(Solution().possibleBipartition(n, dislikes))

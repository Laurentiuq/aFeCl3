from collections import defaultdict


class Solution:
    def criticalConnections(self, n: int, connections: list[list[int]]) -> list[list[int]]:
        # lista de adiacenta
        adjList = defaultdict(list)
        for pair in connections:
            adjList[pair[0]].append(pair[1])
            adjList[pair[1]].append(pair[0])

        ranks = [-2] * n  # rank pentru fiecare nod
        critConnections = set()

        def DFS(node, rank):
            # print(node)
            if ranks[node] >= 0 or ranks[node] == -3:  # daca nodul are rank inseamna ca a mai fost vizitat
                return ranks[node]

            min_rank_current_dfs = rank  # rank-ul minim accesibil din dfs ul curent
            ranks[node] = rank  # actualizam rank ul
            # min_desc_rank = n
            for nextNode in adjList[node]:
                if ranks[nextNode] != rank - 1 and ranks[nextNode] != -3:  # exceptam daca este parinte sau daca e vizitat complet
                    min_desc_rank = DFS(nextNode, rank + 1)  # rank-ul minim al descendentilor accesibil din nextNode(si care nu au mai fost vizitati)
                    # daca exista vreun descendent cu rank mai mic decat rank-ul actual
                    # inseamna ca am gasit un ciclu, deci muchiile din ciclul respectiv nu sunt criticalConnect.
                    # daca un descendent are rank-ul mai mare decat rank ul parintelui atunci nu face parte din niciun ciclu comun cu parintele deci este muchie critica
                    if min_desc_rank > rank:
                        # print("HERE", min_desc_rank, node, rank)
                        critConnections.add(tuple(sorted((node, nextNode))))
                        # print(critConnections)

                    min_rank_current_dfs = min(min_desc_rank, min_rank_current_dfs)
            # print(node, min_rank_current_dfs)
            ranks[node] = -3  # e complet vizitat
            return min_rank_current_dfs

        DFS(0, 0)
        # print(ranks)
        return list(critConnections)
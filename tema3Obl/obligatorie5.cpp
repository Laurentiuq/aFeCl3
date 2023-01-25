// Detectarea ciclurilor Hamiltoniene folosind bit mask
// folosim o reprezentare pe biti pentru a retine multimile de varfuri in loc de permutari
// o permutare reprezinta un ciclu hamiltonian
// pe masura ce gasim noduri care pot sa fie adaugate in ciclu reunim permutarile ( or pe biti)
// in acest caz permutarea e multimea ordonata care retine pe ce pozitie a fost gasit un nod
// cand ajungem la o reprezentare de forma 1111111 inseaman ca am gasit un ciclu cu toate nodurile

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int dim = graph.size();
        int sol = 0;
        queue<pair<int,int>> q;
        // stare = multimea de varfuri in care se afla un nod
        // daca am vizitat un nod care se afla intr-o anumit stare
        vector<vector<bool>> visited(dim + 1, vector<bool>(1 << dim, false));

        // adaugam in coada nodul si permutarea care contine doar nodul respectiv
        for(int i = 0; i < dim; i++)
            q.push(make_pair(i, 1<<i));

        while(!q.empty()){
            for(int s = q.size(); s > 0; s--){
                int cNode = q.front().first;
                int state = q.front().second;
                q.pop();
                // daca am gasit o permutare care contine toate nodurile
                // adica are toti bitii 1
                if (state == (1 << dim) - 1)
                    return sol;
                // daca gasim un nod deja vizitat in starea actual sarim la urmatorul
                if(visited[cNode][state])
                    continue;
                // setam nodul actual ca vizitat pentru starea actuala
                visited[cNode][state] = true;
                // pentru fiecare nod din graf nevizitat, adaugam in q nodul si noua stare
                // (reunim multimea cu nodul actual cu fiecare nod din graf)
                // in biti e echivalent cu or intre starea actuala si multimea cu bitul noului element
                // (0000010) | (0000100) = (0000110) -> multimea in care avem nodul 2 reunita cu multimea cu nodul 3
                for(int el : graph[cNode])
                    q.push(make_pair(el, state | (1<<el)));
            }
            sol++;
        }
    return -1;
    }
};


int main()
{
    Solution s;
    vector<vector<int>> graph = {{1,2,3},{0},{0},{0}};
    vector<vector<int>> graph2 = {{1},{0,2,4},{1,3,4},{2},{1,2}};

    cout<<s.shortestPathLength(graph);
    return 0;
}

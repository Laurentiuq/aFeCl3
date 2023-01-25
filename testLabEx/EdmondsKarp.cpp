/*
 * Facem BFS si cat timp gasim un drum de crestere, aflam fluxul maxim ce poate sa fie trimis pe acel
 * drum de crestere (minimul dintre fluxul maxim ce poate fi trimis pe fiecare muchie).
 * Parcurgem arborele BFS de la destinatie spre sursa (pentru mai multe drumuri daca e posibil)
 * si pastram minimul corespunzator pe drumul parcurs (cu vectorul de tati).
 * Parcurgem inca o data arborele si actualizam graful si arcele inverse (tin loc de rezidual) cu capacitatile ramase
 * O(m*L)
*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
ifstream in("maxflow.in");

vector<int> adjList [5005];
int cap[5005][5005];
int n,m;
void read(){
    in >> n >>m;
    int x, y, z;
    for(int i = 0; i < m; i++)
    {
        in >> x >> y >> z;
        adjList[x].emplace_back(y);
        // retinem si arcele inverse (in loc de graf rezidual) in aceeasi lista de adiacenta
        adjList[y].emplace_back(x);
        cap[x][y] = z;
    }
}

int BFS(int source, int dest, vector<int>& parent)
{

    fill(parent.begin(), parent.end(), -1);
    parent[source] = 0;
    queue<int> q;
    q.push(source);
    while(!q.empty()) {
        int pNode = q.front(); //nodul parinte
        q.pop();
        for (auto el: adjList[pNode])
        {
            int cNode = el; // copiii nodului parinte actual
            if(cNode != pNode && parent[cNode] == -1 && cap[pNode][cNode] > 0)
            {
                parent[cNode] = pNode;
                if(cNode == dest)
                {
                    return 1;
                }
                //adaugam urmatorul nod ce urmeaza sa fie vizitat
                q.push({cNode});
            }
        }
    }
    return 0;
}


int FordFulkerson(int source, int dest)
{
    vector<int> parent(n + 1, -1);
    int mxFlow = 0;


    while(BFS(source,dest,parent)) {
        // folosim arborele BFS (vectorul de tati) pentru a parcurge cat mai multe drumuri care pornesc din destinatie
        // daca este posibil(au un nod parinte in vectorul de tati)
        for (auto el: adjList[dest]) {
            // calculam cat flux putem trimite pe drumul de crestere actual
            if (parent[el] != -1) {
                int mnCap = INT_MAX;
                int cNode = dest;
                parent[dest] = el;
                while (cNode != source) {
                    mnCap = min(mnCap, cap[parent[cNode]][cNode]);
                    cNode = parent[cNode];
                }
                // actualizam graful (si pentru arcele inverse)
                cNode = dest;
                while (cNode != source){
                    cap[cNode][parent[cNode]] += mnCap;
                    cap[parent[cNode]][cNode] -= mnCap;
                    cNode = parent[cNode];
                }
                mxFlow += mnCap;
            }
        }
    }
    return mxFlow;
}


int main()
{
    read();

    cout<<FordFulkerson(1, n);
    return 0;
}
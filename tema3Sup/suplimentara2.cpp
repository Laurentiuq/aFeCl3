#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
// Solutia este numarul de varfuri minus cuplajul maxim
// Ford-Fulkerson returneaza numarul de muchii din graf pentru cuplaj maxim(fluxul maxim)
// Cand construim o acoperire sau adaugam o muchie la un drum existent, sau cream un nou drum cu un nod de inceput si fara muchie(de lungime 0)
// In prima varianta creste numarul de muchii adaugate si ramane constant nr de drumuri
// In a doua creste nr de drumuri si raman constante muchiile
// Astfel, cele doua sunt complementare si cand vom parcurge toate cele n varfuri o sa avem nr_drumuri + nr_muchii = n
// Stim ca in cuplajul maxim avem nr_muchii = flux => nr_drumuri = n - nr_muchii
using namespace std;
//using namespace std::chrono;
//ifstream in("maxflow.in");
//ofstream out("maxflow.out");
ifstream in("drumuri2.in");
ofstream out("drumuri2.out");
vector<vector<int>> adjList;
unordered_map<int, int> cap[20005];
unordered_map<int,int> sol;
vector<bool> viz(20005, false);
struct muchie{

};
int n,m;
void read(){
    in >> n >> m;
    adjList.resize(n + n + 3);
//    cap.resize(n + n + 3, vector<int>(n + n + 3, 0));
    int x, y;
    for(int i = 0; i < m; i++)
    {
        in >> x >> y;
        adjList[x].emplace_back(y+n);
        adjList[y + n].emplace_back(x);
        cap[x][y+n] = 1;

    }

    for(int i = 1; i <= n; i++)
    {
        adjList[0].emplace_back(i);
//        adjList[i].emplace_back(0);
        cap[0][i] = 1;
    }
    for(int i = 1; i <= n; i++)
    {
        adjList[i + n].emplace_back(n + n + 1);
        adjList[n + n + 1].emplace_back(i + n);
        cap[i + n][n+n+1] = 1;

    }

    for(int i = 1; i <= n; i++) {
        adjList[n+i].emplace_back(i);
        adjList[i].emplace_back(n+i);
        cap[n + i][i] = 1;
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
            if(cNode != pNode && parent[cNode] == -1  && cap[pNode][cNode] > 0)
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
    vector<int> parent(n + n + 3, -1);
    int mxFlow = 0;


    while(BFS(source,dest,parent)) {

        for (auto el: adjList[dest]) {
            if (parent[el] != -1) {
                int mnCap = INT_MAX;
                int cNode = dest;
                parent[dest] = el;
                while (cNode != source) {
                    mnCap = min(mnCap, cap[parent[cNode]][cNode]);
                    cNode = parent[cNode];
                }
                cNode = dest;
                while (cNode != source){
                    cap[cNode][parent[cNode]] += mnCap;
                    cap[parent[cNode]][cNode] -= mnCap;
                    if(cap[parent[cNode]][cNode] == 0 && parent[cNode] != source  && cNode != n + n + 1)
                        sol[parent[cNode]] = cNode - n;
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
    out<<n - FordFulkerson(0, n + n + 1)<<endl;


    return 0;
}
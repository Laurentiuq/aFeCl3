// Folosim un alogritm de detectie a drumurilor/ciclurilor euleriene pe partile din graf care permit asta
// Cand nu mai gasim, algoritmul trece la urmatoarea etapa
// O(m+n)

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

//ifstream in("maxflow.in");
//ofstream out("maxflow.out");
ifstream in("johnie.in");
ofstream out("johnie.out");
//retinem in lista de adiacenta pentru fiecare nod o pereche de tipul
// nodul adiacenta, muchia sub forma unui indice(1-nrMuchii)
vector<pair<int,int>> adjList[100005];
// cnt - la ce etapa ne aflam
int n,m,cnt = -1;
int visited[200010];
// vectorul cu etapele
vector<int> sol[100005];


// cautam drumurile euleriene
void euler(int cPair)
{
    // cat timp mai avem muchii neparcurse
    while(!adjList[cPair].empty())
    {
        pair<int, int> cNode = adjList[cPair].back();
        int nNode = cNode.first;
        int edge = cNode.second;
        adjList[cPair].pop_back();
        // daca muchia e nevizitata o marcam si o eliminam din lista
        if(visited[edge] == 0)
        {
            visited[edge] = 1;
            euler(nNode);
        }
    }
    // daca am gasit o muchie o adaugam la solutie
    // daca nu am gasit trecem la urmatoarea etapa (un fel de cc pe cazul eulerian)
    if(cPair!=0)
        sol[cnt].push_back(cPair);
    else
        cnt++;
}

void read()
{
    in>>n>>m;
    for(int i = 1; i<=m;i++)
    {
        int x,y;
        in>>x>>y;
        adjList[x].emplace_back(make_pair(y,i));
        adjList[y].emplace_back(make_pair(x,i));
    }
    // daca avem noduri cu grad impar, adaugam o muchie cu sursa pentru a fuctiona euler
    // (vrem sa ne putem intoarce eventual prin respectivul nod pentru a nu ne bloca -- avem voie sa trecem de mai multe ori printr-un nod)
    for(int i = 1; i<=n;i++)
    {
        if(adjList[i].size() % 2)
        {
            adjList[i].emplace_back(make_pair(0,++m));
            adjList[0].emplace_back(make_pair(i,m));
        }
    }
}

int main()
{
    
    read();
    
    euler(0);

    out<<cnt<<"\n";

    for(int i = 0; i < cnt; i++)
    {
        out<<sol[i].size()<<" ";
        for(auto it: sol[i])
            out<<it<<" ";
        out<<"\n";
    }

    return 0;
}
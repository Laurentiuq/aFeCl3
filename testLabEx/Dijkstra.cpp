/* Se foloseste Dijkstra adaugand in coada toate forturile si se adauga in coada
 * de prioritati doar urmatoarele noduri care dau o distanta mai mica pana
 * la forturi. Se verifica ordinul forturilor daca se obtine distanta egala si
 * se actualizeaza.
 * O(n^2)
 * */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

ifstream in("maxflow.in");
//ofstream out("catun.out");

const int K = 36005;

// lista de adiacenta
vector<pair<int, int>> adjList[K];

// vectorul cu distanta minima de o fortareata la un catun
vector<long long> dist(K, INT_MAX);



// coada de prioritati cu min heap
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
int n, m;

void read(){
    in>>n>>m;
    int x, y, cost;

    // lista de adiacenta (pereche cost-nod)
    for(int i = 1; i<=m; i++){
        in>>x>>y>>cost;
        adjList[x].emplace_back(cost ,y);
        adjList[y].emplace_back(cost, x);
    }
}

void Dijkstra(int start){
    int cNode, nNode, nCost;
    Q.push(make_pair(0, start));
    dist[start] = 0;
    while(!Q.empty()){
        cNode= Q.top().second;
        Q.pop();

        for(auto nPair : adjList[cNode]){
            nNode = nPair.second;
            nCost = nPair.first;
            if(dist[cNode] + nCost < dist[nNode]){
                dist[nNode] = dist[cNode] + nCost;

                Q.push((make_pair(dist[nNode], nNode)));
            }

        }
//        cout<<endl;
    }
}
int main(){
    read();
    int start;
    cin>>start;
    Dijkstra(start);
    for(int i = 1; i<=n ;i++){
        cout<<i<<" - "<<dist[i]<<endl;
    }
}
/* Se foloseste Dikstra adaugand in coada toate forturile si se adauga in coada
 * de prioritati doar urmatoarele noduri care dau o distanta mai mica pana
 * la forturi. Se verifica ordinul forturilor daca se obtine distanta egala si
 * se actualizeaza.
 * */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

ifstream in("catun.in");
ofstream out("catun.out");

const int K = 36005;

// lista de adiacenta
vector<pair<int, int>> adjList[K];

// vectorul cu distanta minima de o fortareata la un catun
vector<long long> dist(K, INT_MAX);

// vector cu cel mai mic predecesor al unui catun
vector<int> pred(K, 0);

// coada de prioritati cu min heap
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
int n, m, k;

void read(){
    in>>n>>m>>k;
    int x, y, cost;
    // adaugam forturile in coada de prioritati
    for(int i = 1; i<=k; i++){
        in>>x; // fortareata
        dist[x] = 0;  // distanta de la fort la fort e 0
        pred[x] = x; // predecesorul fortului e fortul
        Q.push(make_pair(0, x));
    }
    // lista de adiacenta (pereche cost-nod)
    for(int i = 1; i<=m; i++){
        in>>x>>y>>cost;
        adjList[x].emplace_back(cost ,y);
        adjList[y].emplace_back(cost, x);
    }
}

void Dijkstra(){
    int cNode, nNode, nCost;
    while(!Q.empty()){
        cNode= Q.top().second;
        Q.pop();

        for(auto nPair : adjList[cNode]){
            nNode = nPair.second;
            nCost = nPair.first;
//            cout<<nNode<<" "<< dist[nNode]<<" "<<dist[cNode] + nCost<<"  , ";
            // daca obtinem o distanta mai mare actualizam distanta si predecesorul
            // adaugam in coada urmatoarul nod conform distantei
            if(dist[cNode] + nCost < dist[nNode]){
                dist[nNode] = dist[cNode] + nCost;
                pred[nNode] = pred[cNode];
                Q.push((make_pair(dist[nNode], nNode)));
            }
            // daca obtinem o distanta egal actualizam doar predecesorul
            else if(dist[cNode] + nCost == dist[nNode])
            {
                // alegem predecesorul mai mic, verificam sa nu actualizam predecesorul unui fort
                if(pred[cNode] < pred[nNode] && pred[nNode] != nNode) {
                    pred[nNode] = pred[cNode];
                }
            }
        }
//        cout<<endl;
    }
}
int main(){
    read();
    Dijkstra();
    for(int i = 1; i<=n ;i++){
        if(dist[i] == INT_MAX || pred[i] == i)
            out<<0<<" ";
        else
            out<<pred[i]<<" ";
    }
}
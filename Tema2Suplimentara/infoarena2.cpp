// Folosim union-find pentru a aplic un Kruskal modificat, atunci cand gasesc o muchie care uneste doua componente conexe
// verific in lista de queries daca exista o muchie care sa lege aceleasi doua componente conexe (gasim o pereche de noduri
// din muchiile exotice care au acelasi reprezentant cu o pereche de noduri ce determina o muchie din multimea drumurilor normale)
// costul drumului exotice trebuie sa fie cu 1 mai putin decat cel mai mic cost gasit in muchiile normale

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<int> sets, ranks;

struct Edge{
    int node1, node2, cost;
};

bool comp(Edge& x1, Edge& x2){
    return x1.cost < x2.cost;
}

void uni(int x, int y){
    if(ranks[x] > ranks[y])
        sets[y] = x;
    else
        sets[x] = y;
    if(ranks[x] == ranks[y])
        ranks[y]++;
}

int find(int x){
    if(sets[x] != x)
        sets[x] = find(sets[x]);
    return sets[x];
}

vector<Edge> edgeList, queries;
vector<int> sol;
//ifstream in("ctc.in");
//ofstream out("ctc.out");
ifstream in("apm2.in");
ofstream out("apm2.out");

int n,m, Q;

void Kruskal() {

    for(int i = 0; i < n + 1; i++)
    {
        sets[i] = i;
        ranks[i] = 1;
    }


    sort(edgeList.begin(), edgeList.end(), comp);


    for(auto el: edgeList)
        // aplic union find si pentru fiecare muchie din graf, daca gasesc in query o muchie care leaga aceleasi compomente
        // conexe cu cea din graf costul minim o sa fie costul minim al unei muchii - 1(care conecteaza cele doua componente conexe)
        if(find(el.node1) != find(el.node2)) {
            for(int q = 0; q < Q; q++) {
                if(queries[q].cost == -1) //daca al q-lea query nu a are un raspuns si uneste doua componente conexe pe care le mai uneste si o muchie din graf
                    if(find(el.node1) == find(queries[q].node1) && find(el.node2) == find(queries[q].node2) || find(el.node1) == find(queries[q].node2) && find(el.node2) == find(queries[q].node1)) {
                        queries[q].cost = el.cost - 1;

                    }

            }
            uni(find(el.node1), find(el.node2));
        }
}



int main(){
    int k;
    in >> n >> m >> Q;
    sets.resize(n + 1);
    ranks.resize(n + 1);
    sol.resize(Q + 1);
    Edge Edge{};
    for(int i = 0; i < m; i++){
        in>>Edge.node1>>Edge.node2>>Edge.cost;
        edgeList.push_back(Edge);
    }
    for(int i = 0; i < Q; i++){
        in>>Edge.node1>>Edge.node2;
        Edge.cost = -1;
        queries.emplace_back(Edge);
    }
    Kruskal();
    for(int i =0 ;i<Q;i++)
        out<<queries[i].cost<<endl;
    return 0;
}
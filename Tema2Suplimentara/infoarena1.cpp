// gasim primul APM si retinem ce muchii contine
// Adaugam noua muchie la muchiile APM-ului si aplicam Kruskal pe ele. Daca gasim un APM mai mic cu noua muchie
// aceasta va fi adaugata in APM
// ( cand adaug o noua muchie in APM formeaza un ciclu si aplicand din nou Kruskal o sa elimine muchia de cost maxim din ciclu)

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

vector<Edge> edgeList, apm;

//ifstream in("ctc.in");
//ofstream out("ctc.out");
ifstream in("online.in");
ofstream out("online.out");

int n,m;

void Kruskal() {

    for(int i = 0; i < n + 1; i++)
    {
        sets[i] = i;
        ranks[i] = 1;
    }


    sort(edgeList.begin(), edgeList.end(), comp);


    int cost = 0;

    for(auto el: edgeList)
        if(find(el.node1) != find(el.node2)) {
            uni(find(el.node1), find(el.node2));
            cost += el.cost;
            // salvam muchiile din APM
            apm.push_back(el);
        }
    // urmatorul Kruksal o sa fie aplicat pe muchiile din APM plus o noua muchie
    edgeList = apm;
    apm.clear();
    out<<cost<<endl;
}



int main(){
    int k;
    in >> n >> m;
    sets.resize(n + 1);
    ranks.resize(n + 1);
    Edge Edge{};
    for(int i = 0; i < m; i++){
        in>>Edge.node1>>Edge.node2>>Edge.cost;
        edgeList.push_back(Edge);
    }
    Kruskal();
    in>>k;
    for(int i = 0; i<k; i++){
        in>>Edge.node1>>Edge.node2>>Edge.cost;
        edgeList.push_back(Edge);
        Kruskal();
    }

    return 0;
}
// Un fel de Bellman-Ford dar in loc de cicluri negative cautam orice ciclu
// Relaxam nodurile daca gasim un nod care contribuie (negativ) la medie
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

//ifstream in("ctc.in");
//ofstream out("ctc.out");
ifstream in("ciclu.in");
ofstream out("ciclu.out");

int n, m;
vector<pair<int, int>> adjList[1005];
void read(){
    in>>n>>m;
    int node1, node2, cost;
    for(int i = 0; i < m; i++){
        in>>node1>>node2>>cost;
        adjList[node1].emplace_back(make_pair(node2, cost));
    }
}

int cycle(double mij){
    vector<double> dist(n + 1, 0);
    vector<int> nrNodes(n + 1, 0);

    queue<int> q;
    for(int i = 1; i <= n; i++)
        q.push(i);
    int cNode;
    while(!q.empty()){
        cNode = q.front();
        q.pop();

        for(auto el : adjList[cNode]){
            // daca distanta data de nodul curent minus valoare gasita in binary search e mai mica decat distanta data de urmatorul nod
            // cand nu mai gasim q se goleste si ne aflam la ciclul cu media minima
            if(dist[cNode] + el.second - mij < dist[el.first]){
                dist[el.first] = dist[cNode] + el.second - mij;
                // numaram numarul de noduri gasite pentru a stii cand am obtinut un ciclu
                nrNodes[el.first]++;
                if (nrNodes[el.first] >= n)
                    return 1;
                // daca nu am obtinut un ciclu
                q.push(el.first);
            }
        }
    }
    return 0;
}

double binarySearch(){
    double l = 0, r = 4000005, sol, mij;
    while(l < r){
        mij = ((l + r)/2);
        if(cycle(mij)) {
            r = mij - 0.001;
            sol = mij;
        }
        else
            l = mij + 0.001;
    }
    return sol;
}


int main(){

    read();
    out<<fixed<<setprecision(2)<<binarySearch();
    return 0;
}
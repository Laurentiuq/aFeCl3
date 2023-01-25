/*
 * Folosim sortarea topologica si retinem pentru fiecare nod drumul de valoare maxima care exista pana la el
 * Sortarea topologica ne asigura ca parcurgem nodurile in ordinea drumurilor, alegand drumul de valoare maxima
 * pana la pasul curent
 * Parcurgerea in ordine topologica merge in directia drumurilor
 * */
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

ifstream in("easygraph.in");
ofstream out("easygraph.out");

const int N = 15005;
const long long mn = LONG_LONG_MIN;
// lista de adiacenta
vector<vector<int>> adjList;

vector<long long> valori;

// coada de prioritati
queue<int> Q;

vector<int> inGrad;
int t, n, m;

void read() {
    in >> n >> m;
    valori.resize(n + 1, 0);
    adjList.resize(n + 1, vector<int>());
    inGrad.resize(n + 1, 0);
    int x, y, cost;
    for (int i = 1; i <= n; i++) {
        in >> cost;
        valori[i] = cost;
    }
    for (int i = 1; i <= m; i++) {
        in >> x >> y;
        adjList[x].emplace_back(y);
        inGrad[y]++;
    }

}

long long TopSort() {
    long long cNode, nValoare, drMx = mn;
    vector<long long> valoriMx(n + 1, mn);
    for (int i = 1; i <= n; i++)
        if (inGrad[i]==0) {
            Q.push(i);

        }
    for (int i = 1; i <= n; i++) {
        valoriMx[i] = valori[i];
        if (drMx < valori[i])
            drMx = valori[i];
    }
    while (!Q.empty()) {
        cNode = Q.front();
        Q.pop();
        for (auto nNode: adjList[cNode]) {
            nValoare = valoriMx[cNode] + valori[nNode];
            if (valoriMx[nNode] < nValoare) {
                valoriMx[nNode] = nValoare;
                if (drMx < nValoare)
                    drMx = nValoare;
            }
            inGrad[nNode]--;
            if (inGrad[nNode]==0)
                Q.push(nNode);
        }
    }
    return drMx;
}

int main() {
    in >> t;
    for (int i = 1; i <= t; i++) {
        Q = queue<int>();
        valori.clear();
        for(int j = 1; j <= n;j++)
            adjList[j].clear();
        adjList.clear();
        inGrad.clear();
        read();
        out << TopSort() << endl;
    }
    return 0;
}
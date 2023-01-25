// Folosim Bellman-Ford pentru a afla costul minim de la sursa la orice nod
// Foslosim costul calculat pentru a transforma costul muchilor in cost pozitiv
// Pentru fiecare muchie (u,v), adaugam la costul ei costul (s,u) si scadem (s,v)
// pentru ca cost(s,u) + cost(u,v) > cost(s,v), altfel cost(s,v) nu ar fi minim
// Retinem costurile nemodificate(adevarate) pentru calcularea costului final(nr_flux * (cost per u.m. flux))
// Pentru ca avem ponderi pozitive putem folos dijkstra pentru a determina drumurile de crestere
// O(m*log(n) * n^2)
// Bellman-Ford O(m * n)
// Dijkstra O(m*log(n)) - coada de prioritati

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

ifstream in("fmcm.in");
ofstream out("fmcm.out");


vector<int> adjList[352];
int bfDist[352]; // distanta minima din bellman-ford(costul)
// capacitatea, cat flux trece la un moment prin muchie(pe graful rezidual cu minus), costul muchiei
int cap[352][352], cFlux[352][352], cost[352][352];
int n, m, source, dest;

void BellmanFord() {
    for (int i = 1; i <= n; i++)
        bfDist[i] = INT_MAX;
    queue<int> q;

    bfDist[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int nNode: adjList[node])
            if (cap[node][nNode] > 0) {
                if (bfDist[node] + cost[node][nNode] < bfDist[nNode]) {
                    bfDist[nNode] = bfDist[node] + cost[node][nNode];
                    q.push(nNode);
                }
            }
    }
}

// dist(cost) doar pozitiv, costul real, parintele
int dist[352], realCost[352], parent[352];

bool visited[352];


// cauta un drum de crestere
bool Dijkstra() {
    for (int u = 1; u <= n; u++) {
        parent[u] = -1;
        dist[u] = INT_MAX;
        visited[u] = false;
    }

    priority_queue<pair<int, int>> q;

    dist[source] = 0;
    realCost[source] = 0;
    parent[source] = 0;
    q.push(make_pair(-dist[source], source));

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if(visited[u])
            continue;

        visited[u] = true;

        for (int v: adjList[u])
            if (cFlux[u][v] < cap[u][v]) {
                if (dist[u] + ((bfDist[u] - bfDist[v]) + cost[u][v]) < dist[v]) {
                    // calculam noul cost
                    dist[v] = dist[u] + ((bfDist[u] - bfDist[v]) + cost[u][v]);
                    // costul real al drumului de crestere
                    realCost[v] = realCost[u] + cost[u][v];
                    parent[v] = u;
                    q.push(make_pair(-dist[v], v));
                }
            }
    }
    // actualizam costurile pentru urmatorul drum de crestere
    // costul minim gasit de Dijkstra pentru muchile din componenta unui drum de crestere
    // (ne intereseaza doar muchiile care se afla pe un drum de crestere)
    for (int u = 1; u <= n; u++)
        bfDist[u] = realCost[u];

    return parent[dest] != -1;

}

// gasim fluxul maxim doar ca tinem minte si costul(real) pentru fiecare drum de crestere
int FordFulkerson() {
    int mxFlow = 0;
    while (Dijkstra()) {
        int mnCap = INT_MAX, sCost = 0;
        int u = dest;
        while (u != source) {

            int v = parent[u];
            mnCap = min(mnCap, cap[v][u] - cFlux[v][u]);
            sCost += cost[v][u];
            u = v;
        }
        u = dest;
        while (u != source) {

            int v = parent[u];
            cFlux[v][u] += mnCap;
            cFlux[u][v] -= mnCap;
            u = v;
        }
        // costul pentru cate unitati de flux putem trimite
        mxFlow += sCost * mnCap;
    }
    return mxFlow;
}

int main() {

    in >> n >> m >> source >> dest;

    for (int i = 1; i <= m; i++) {
        int u, v, capacitate, vcost;
        in >> u >> v >> capacitate >> vcost;

        adjList[u].push_back(v);
        adjList[v].push_back(u);

        cost[u][v] = vcost;
        cost[v][u] = -vcost;

        cap[u][v] = capacitate;
        cap[v][u] = 0;

        cFlux[u][v] = 0;
        cFlux[v][u] = 0;


    }

    BellmanFord();

    out << FordFulkerson() << "\n";

    return 0;
}
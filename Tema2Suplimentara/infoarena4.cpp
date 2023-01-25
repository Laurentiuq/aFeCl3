// Folosim un algoritm asemanator cu Dijkstra doar ca retine rezultatele intr-o matrice astfel sa putem obtine
// pentru un numar de watti ramasi si un nod ce distanta am parcurs
// Gasim care ar fi timpul minim daca am avea o lanterna cu capacitate maxima si apoi folosind binary search
// cautam o lanterna cu capacitate minima care ne obtine acelasi timp (minim)

#include <iostream>
#include <bits/stdc++.h>

using namespace std;


//ifstream in("ctc.in");
//ofstream out("ctc.out");
ifstream in("lanterna.in");
ofstream out("lanterna.out");

int n, k, m;
// bazele inamice sau aliate
vector<int> bases;

// lista de adiacenta cu tuplu de forma {baza militara catre care merge, timpul necesar, numarul de watti}
vector<tuple<int, int, int>> adjList[55];


void read() {
    in >> n >> k;
    bases.resize(n + 1);
    for (int i = 1; i <= n; i++)
        in >> bases[i];
    in >> m;
    int node1, node2, time, watt;
    for (int i = 0; i < m; i++) {
        in >> node1 >> node2 >> time >> watt;
        adjList[node1].emplace_back(node2, time, watt);
        adjList[node2].emplace_back(node1, time, watt);
    }
}

// intr-o matrice retin timpul pe care l-am parcurs pentru a ajunge intr-un nod
// pentru un numar de watti ramasi, avand o capacitate de wattK watti(maxim)
// liniile reprezinta nodul in care am ajuns si coloanele numarul de watti cu care am ajuns in acel nod


int Dijkstra(int wattK) {
    vector<vector<int>> time(n + 1, vector<int>(k + 1,INT_MAX));
    queue<tuple<int, int, int>> q;
    time[1][wattK] = 0;
    q.push(make_tuple(1, 0, wattK));
    tuple<int, int, int> currentEdge;

    int mn = INT_MAX;
    while(!q.empty()) {
        currentEdge = q.front();
        int currentEdgeNode = get<0>(currentEdge), currentEdgeTime = get<1>(currentEdge), currentEdgeWatt = get<2>(currentEdge);
        q.pop();
//        int remWatts  = currentEdgeWatt;

        for (auto nextEdge: adjList[currentEdgeNode]) {
            int nextEdgeNode = get<0>(nextEdge), nextEdgeTime = get<1>(nextEdge), nextEdgeWatt = get<2>(nextEdge);
            int  remWatts = currentEdgeWatt - nextEdgeWatt;

            if (bases[nextEdgeNode])
                remWatts = wattK;

            //daca gasesc un drum mai scurt si care costa mai putini watti il actualizez in matrice
            if (nextEdgeWatt <= currentEdgeWatt && time[nextEdgeNode][remWatts] > time[currentEdgeNode][currentEdgeWatt] + nextEdgeTime) {
                time[nextEdgeNode][remWatts] = time[currentEdgeNode][currentEdgeWatt] + nextEdgeTime;
                q.push(make_tuple(nextEdgeNode, nextEdgeTime, remWatts));
            }
//            if(nextEdgeNode == n)
//                mn = min(time[n][remWatts], mn);
        }
    }

    for(int i = 0; i <= wattK; ++i)
        mn = min(time[n][i], mn);
//    return mini;
    return mn;
}

// pentru drumul de timp minim caut numarul minim de watti pe care trebuie sa ii aiba lanterna pentru
// a obtine acel drum minim
int binarySearch(int mnTime){
    int l = 1, r = k, mid, sol = k;
    while(l <= r){
        mid = (l+r)/2;
        // aplic 'dijkstra' pentru a afla drumul minim pe care il pot obtine avand o capacitate de mid watti
        // daca gasesc un drum minim egal cu drumul minim obtinut pt nr maxim de watti actualizez solutia
        // binary search continua dupa ce am gasit un drum in cazul in care gasesc unul pt o capacitate mai mica de watti
        //  (cautam in stanga)
        if(Dijkstra(mid) == mnTime)
        {
            r = mid - 1;
            sol = mid;
        }
        else
            l = mid + 1;
    }
    return sol;
}

int main() {
    read();
    // timpul minim pe care il putem obtine considerand lanterna cu capacitate maxima de watti
    int mnTime = Dijkstra(k);
    out<<mnTime<<" ";
    out<<binarySearch(mnTime);
    return 0;
}
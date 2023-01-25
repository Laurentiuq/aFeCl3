#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;
using namespace std::chrono;
ifstream in("maxflow.in");
ofstream out("maxflow.out");
//ifstream in("cuplaj.in");
//ofstream out("cuplaj.out");
vector<int> adjList[20005];
unordered_map<int, int> cap[20005];
unordered_map<int, int> sol;
unordered_map<int, vector<int>> sol2;

int n, m, p;
int k = INT_MAX;

void read() {
    in >> n >> m >> p;
//    adjList.resize(n + m + 3);
//    cap.resize(n + m + 3, vector<int>(n + m + 3, 0));
    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        adjList[x].emplace_back(y);
        adjList[y].emplace_back(x);
        cap[x][y] = 1;
    }
    for (int i = 1; i <= p; i++) {
        adjList[0].emplace_back(i);
//        adjList[i].emplace_back(0);
        cap[0][i] = 1;
    }
    for (int i = p + 1; i <= n; i++) {
        adjList[i].emplace_back(n + 1);
        adjList[n + 1].emplace_back(i);
        cap[i][n + 1] = 1;
    }
}


void read2f() {
    in >> n >> m >> p;
//    adjList.resize(n + m + 3);
//    cap.resize(n + m + 3, vector<int>(n + m + 3, 0));
    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        adjList[x].emplace_back(y);
        adjList[y].emplace_back(x);
        cap[x][y] = 1;
        cap[y][x] = 1;
    }
    for (int i = 1; i <= p; i++) {
        adjList[0].emplace_back(i);
//        adjList[i].emplace_back(0);
        cap[0][i] = 2;
        cap[i][0] = 2;
    }
    for (int i = p + 1; i <= n; i++) {
        adjList[i].emplace_back(n + 1);
        adjList[n + 1].emplace_back(i);
        cap[i][n + 1] = 2;
        cap[n+1][i] = 2;
    }
}

int BFS(int source, int dest, vector<int> &parent) {

    fill(parent.begin(), parent.end(), -1);
    parent[source] = 0;
    queue<int> q;
    q.push(source);
    while (!q.empty()) {

        int pNode = q.front(); //nodul parinte
        q.pop();
        for (auto el: adjList[pNode]) {
            int cNode = el; // copiii nodului parinte actual
            if (cNode != pNode && parent[cNode] == -1 && cap[pNode][cNode] > 0) {
                parent[cNode] = pNode;
                if (cNode == dest) {
                    return 1;
                }
                //adaugam urmatorul nod ce urmeaza sa fie vizitat
                q.push(cNode);
            }
        }
    }
    return 0;
}


int EdmondsKarp(int source, int dest) {
    vector<int> parent(n + m + 3, -1);
    int mxFlow = 0;

    int nr = 0;
    while (BFS(source, dest, parent)) {

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
                while (cNode != source) {
                    cap[cNode][parent[cNode]] += mnCap;
                    cap[parent[cNode]][cNode] -= mnCap;
                    if (cap[parent[cNode]][cNode] == 0 && parent[cNode] != 0 && cNode != n + 1) {
                        sol[parent[cNode]] = cNode ;
                        sol2[parent[cNode]].emplace_back(cNode);
                        nr++;
                    }
                    if (nr == k)
                        return mxFlow;
                    cNode = parent[cNode];
                }
                mxFlow += mnCap;
            }
        }
    }
    return mxFlow;
}

int main() {
//    read();
//    cin >> k;
//    int exista = EdmondsKarp(0, n+1);
//    if(exista > 0)
//        out<<"Exista\n";
//    else
//        out<<"Nu exista\n";
//
//    for (int i = 1; i <= n; i++) {
//        if (sol[i] != 0 && i != 0 && sol[i] != n + 1)
//            out << i << " " << sol[i] << endl;
//    }


    out<<"\n------------------------------------\n\n";
    read2f();
    int exista = EdmondsKarp(0, n+1);
    cout<<exista<<endl;
    if(exista > 0)
        out<<"Exista\n";
    else
        out<<"Nu exista\n";

    for (int j = 1; j <= n; j++) {
        for(auto sol: sol2[j]) {
            if (sol != 0 && j != 0 && sol != n + 1)
                out << j << " " << sol << endl;
        }
    }
    return 0;
}
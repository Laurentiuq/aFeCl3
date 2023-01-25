#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

void DAGShortestPath(vector<vector<pair<int, int>>> &adjList, int n, int s) {
    vector<int> dist(n, INF);
    dist[s] = 0;
    stack<int> topo;

    vector<int> in_degree(n);
    for (int i = 0; i < n; i++)
        for (auto [v, w] : adjList[i])
            in_degree[v]++;

    for (int i = 0; i < n; i++)
        if (!in_degree[i])
            topo.push(i);

    while (!topo.empty()) {
        int u = topo.top();
        topo.pop();

        for (auto [v, w] : adjList[u]) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
            if (!--in_degree[v])
                topo.push(v);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Shortest distance from " << s << " to " << i << " is ";
        if (dist[i] == INF) {
            cout << "INF" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<int, int>>> adjList(n);
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        adjList[from].push_back({to, weight});
    }

    DAGShortestPath(adjList, n, s);

    return 0;
}
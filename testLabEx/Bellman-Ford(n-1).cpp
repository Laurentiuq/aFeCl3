#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct Edge {
    int from, to, weight;
};

void BellmanFord(vector<Edge> edges, int n, int s) {
    vector<int> dist(n, INF);
    dist[s] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (auto e : edges) {
            if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.weight;
            }
        }
    }

    for (auto e : edges) {
        if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to]) {
            cout << "Negative cycle detected!" << endl;
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Shortest distance from " << s << " to " << i << " is " << dist[i] << endl;
    }
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        edges.push_back({ from, to, weight });
    }

    BellmanFord(edges, n, s);

    return 0;
}
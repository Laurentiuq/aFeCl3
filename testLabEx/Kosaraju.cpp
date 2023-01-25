#include <bits/stdc++.h>

using namespace std;

void DFS(vector<vector<int>> &adjList, int u, vector<bool> &visited, stack<int> &s) {
    visited[u] = true;
    for (int v : adjList[u]) {
        if (!visited[v]) {
            DFS(adjList, v, visited, s);
        }
    }
    s.push(u);
}

void DFS2(vector<vector<int>> &adjListT, int u, vector<bool> &visited) {
    visited[u] = true;
    cout << u << " ";
    for (int v : adjListT[u]) {
        if (!visited[v]) {
            DFS2(adjListT, v, visited);
        }
    }
}

void Kosaraju(vector<vector<int>> &adjList, int n) {
    vector<bool> visited(n, false);
    stack<int> s;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFS(adjList, i, visited, s);
        }
    }

    vector<vector<int>> adjListT(n);
    for (int i = 0; i < n; i++) {
        for (int v : adjList[i]) {
            adjListT[v].push_back(i);
        }
    }

    fill(visited.begin(), visited.end(), false);

    while (!s.empty()) {
        int u = s.top();
        s.pop();
        if (!visited[u]) {
            DFS2(adjListT, u, visited);
            cout << endl;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adjList(n);
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        adjList[from].push_back(to);
    }

    Kosaraju(adjList, n);

    return 0;
}
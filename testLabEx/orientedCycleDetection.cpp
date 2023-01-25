const int N = 100;
vector<int> g[N];
bool visited[N];
vector<int> path;

void dfs(int u) {
    visited[u] = true;
    path.push_back(u);
    for (int v : g[u]) {
        if (visited[v]) {
            cout << "Cycle found: ";
            for (int i = path.size() - 1; i >= 0; i--) {
                if (path[i] == v) break;
                cout << path[i] << " -> ";
            }
            cout << v << endl;
        } else {
            dfs(v);
        }
    }
    path.pop_back();
    visited[u] = false;
}
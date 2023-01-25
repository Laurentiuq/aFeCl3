bool dfs(int u, int parent) {
    visited[u] = true;
    for (int v : adjList[u]) {
        if (!visited[v]) {
            if (dfs(v, u)) {
                return true;
            }
        } else if (v != parent) {
            return true;
        }
    }
    return false;
}
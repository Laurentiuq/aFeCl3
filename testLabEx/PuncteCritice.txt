#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adjList;
vector<int> low;
vector<int> dfsNum;
vector<bool> onStack;
vector<int> scc;
vector<int> criticalNodes;
stack<int> stk;
int dfsCounter;

void tarjanSCC(int u) {
    dfsNum[u] = low[u] = dfsCounter++;
    stk.push(u);
    onStack[u] = true;
    for (int v : adjList[u]) {
        if (dfsNum[v] == -1) {
            tarjanSCC(v);
            low[u] = min(low[u], low[v]);
        } else if (onStack[v]) {
            low[u] = min(low[u], dfsNum[v]);
        }
    }
    if (dfsNum[u] == low[u]) {
        int v;
        do {
            v = stk.top();
            stk.pop();
            onStack[v] = false;
            scc[v] = u;
        } while (u != v);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    adjList.resize(n);
    low.resize(n);
    dfsNum.resize(n);
    onStack.resize(n);
    scc.resize(n);
    fill(dfsNum.begin(), dfsNum.end(), -1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adjList[u].push_back(v);
    }
    for (int i = 0; i < n; i++) {
        if (dfsNum[i] == -1) {
            tarjanSCC(i);
        }
    }
    vector<int> inDegree(n);
    for (int u = 0; u < n; u++) {
        for (int v : adjList[u]) {
            if (scc[u] != scc[v]) {
                inDegree[scc[v]]++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (inDegree[scc[i]] == 0) {
            criticalNodes.push_back
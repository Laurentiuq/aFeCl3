#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

const int MAX_NODES = 100;
const int INF = 1e9;

// Helper function to add edges to the graph
void addEdge(vector<pair<int, int>> adjacencyList[], int u, int v, int w) {
    adjacencyList[u].push_back({v, w});
    adjacencyList[v].push_back({u, w});
}

// Prim's algorithm for MST
void primMST(vector<pair<int, int>> adjacencyList[], int startNode, int numNodes) {
    int parent[MAX_NODES], key[MAX_NODES];
    bool visited[MAX_NODES];

    // Initialize the arrays
    for (int i = 0; i < numNodes; i++) {
        key[i] = INF;
        visited[i] = false;
    }

    // Set the starting node's key to 0 and make it the first visited node
    key[startNode] = 0;
    parent[startNode] = -1;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, startNode});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        visited[u] = true;

        for (auto v : adjacencyList[u]) {
            int weight = v.second;
            int node = v.first;

            if (!visited[node] && key[node] > weight) {
                key[node] = weight;
                pq.push({key[node], node});
                parent[node] = u;
            }
        }
    }

    // Print the MST
    cout << "Edge :" << " Weight" << endl;
    for (int i = 1; i < numNodes; i++) {
        cout << parent[i] << " - " << i << " : " << key[i] << endl;
    }
}
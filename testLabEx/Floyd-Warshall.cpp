#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

void FloydWarshall(vector<vector<int>> &adjMatrix) {
    int n = adjMatrix.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << adjMatrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adjMatrix(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        adjMatrix[i][i] = 0;
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        adjMatrix[from][to] = weight;
    }

    FloydWarshall(adjMatrix);

    return 0;
}
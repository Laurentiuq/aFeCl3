#include <bits/stdc++.h>

using namespace std;


vector<int> visited;
vector<int> adjList[5000];
int ls_viz;
void DFS(int node) {
    visited[node] = 1;
    for (auto nextNode: adjList[node]) {
        if (visited[nextNode] == 0)
            DFS(nextNode);
    }
    ls_viz = node;
}
vector<int> dist(5000,0);
void BFS(int node){
    vector<int> visitedBFS(5000, 0);

    queue<int> q;
    q.push(node);
    int nextLayer = 0, actDist = 1;
    while(!q.empty())
    {
        int cNode = q.front();
        q.pop();
        nextLayer = 0;
        for(auto nNode: adjList[cNode])
            if(!visitedBFS[nNode]){
                nextLayer = 1;
                dist[nNode] = actDist;
                visitedBFS[nNode] = 1;
                q.push(nNode);
            }
        if(nextLayer)
            actDist++;
    }
}

ifstream in("maxflow.in");
ofstream out("maxflow.out");

int main() {
    int n, m, s;
    in>>n>>m;
    visited.resize(n+1,0);
    int node1, node2;
    for (int i = 0; i < m; i++) {
        in>>node1>>node2;

        adjList[node1].push_back(node2);
        adjList[node2].push_back(node1);
    }
    in >> s;

    int last_visited = 0;
    for(int i =1; i<=n; i++)
    {
        if(!visited[i] && last_visited != 0)
        {
            adjList[last_visited].push_back(i);
            adjList[i].push_back(last_visited);
            cout<<i<<" "<<last_visited<<endl;
        }

        if(!visited[i]) {
            DFS(i);
            last_visited = ls_viz;
        }

    }

    BFS(6);
    int mx = -1;
    for(int i = 1; i<=n;i++){
        mx = max(mx, dist[i]);
    }

    cout<<mx;
    return 0;
}
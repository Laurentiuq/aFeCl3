#include <bits/stdc++.h>
using namespace std;


vector<int> dfsPerm;
vector<int> visited;
vector<int> adjList[5000];
void DFS(int node){
    dfsPerm.emplace_back(node);
    visited[node] = 1;
    for(auto nextNode : adjList[node]){
        if(visited[nextNode] == 0)
            DFS(nextNode);
    }
}
ifstream in("maxflow.in");
int main()
{
    int node1,node2,n,m;
    in>>n>>m;
    visited.resize(n+1,0);
    for(int i = 0; i<m;i++){
        in>>node1>>node2;
        adjList[node1].emplace_back(node2);
        adjList[node2].emplace_back(node1);
    }

    DFS(3);
    for(int i = 0; i<dfsPerm.size(); i++)
        cout<<dfsPerm[i]<<endl;

    return 0;
}
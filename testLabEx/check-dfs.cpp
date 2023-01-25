#include <bits/stdc++.h>
using namespace std;


int n,m;
vector<int> orders;
vector<int> dfsPerm;
vector<int> visited;
vector<int> adjList[5000];
bool cmp(int i1, int i2)
{
    if(orders[i1] > orders[i2])
        return false;
    else
        return true;
}

void DFS(int node){
    dfsPerm.emplace_back(node);
    visited[node] = 1;
    for(auto nextNode : adjList[node]){
        if(visited[nextNode] == 0)
            DFS(nextNode);
    }
}
int main(){


    cin>>n>>m;
    orders.resize(n + 1, 0);
    visited.resize(n + 1, 0);
    dfsPerm.clear();
    adjList->clear();
    vector<int> perm;

    int node;
    for(int i = 0; i < n; i++){
        cin>>node;
        perm.emplace_back(node);
        orders[node] = i;

    }

    int node1,node2;
    for(int i = 0; i<m;i++){
        cin>>node1>>node2;
        adjList[node1].emplace_back(node2);
        adjList[node2].emplace_back(node1);
    }

    for(int i = 1; i <= n;i++)
        sort(adjList[i].begin(), adjList[i].end(),  cmp);

    DFS(1);

    if (dfsPerm == perm)
        cout<<1;
    else
        cout<<0;


    return 0;
}
#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> adjList[5000];
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
int n,m;


ifstream in("maxflow.in");
ofstream out("maxflow.out");

int main() {

    in>>n>>m;
    int n1,n2,c;
    for(int i = 1; i<=m; i++)
    {
        in>>n1>>n2>>c;
        adjList[n1].emplace_back(make_pair(c,n2));
        adjList[n2].emplace_back(make_pair(c,n1));

    }

    int k;
    vector<int> surse;
    vector<int> visited(n+1,0);
    vector<int> key(n+1,INT_MAX);
    vector<int> ances(n+1, 0);
    in>>k;
    vector<int> sourceNr(k, 0);
    vector<int> parent(n+1,0);
    for(int i = 1; i<=k;i++)
    {
        int s;
        in>>s;
        ances[s] = s;
        key[s] = 0;
        q.push(make_pair(0,s));
        surse.push_back(s);
    }

    while(!q.empty()){
        int cNode = q.top().second;
        q.pop();
        visited[cNode] = 1;

        for(auto nNodePair : adjList[cNode]){
            int cost = nNodePair.first;
            int nNode = nNodePair.second;
            if(!visited[nNode] && cost < key[nNode] )
            {
                key[nNode] = cost;
                q.push(make_pair(cost, nNode));
                ances[nNode] = ances[cNode];
                parent[nNode] = cNode;
                sourceNr[ances[nNode]]++;
            }
        }
    }
    for(int i = 1; i<= n; i++){
        if(parent[i]!=0)
            cout<<parent[i]<<" "<<i<<endl;
    }
    int imp = -1;
    int nodCuImpMax = -1;
    for(int i = 1; i<=k;i++){
        if(sourceNr[i] > imp)
        {
            imp = sourceNr[i];
            nodCuImpMax = i;
        }
    }

    cout<<nodCuImpMax;
    return 0;
}
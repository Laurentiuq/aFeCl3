#include <bits/stdc++.h>

using namespace std;


//ifstream in("maxflow.in");
//ofstream out("maxflow.out");

ifstream in("transport2.in");
ofstream out("transport2.out");

// Dijkstra dar il pun sa aleaga muchia de cost maxim la fiecare pas
// In distante eu adaug minimul 

bool visited[100001];
int n, m;
vector<int> dist;
vector<vector<pair<int, int>>> cost;

void Dijkstra(vector<int> &dist, vector<vector<pair<int, int>>>& cost){

    dist[1] = INT_MAX;
    priority_queue <pair<int, int>> Q;
    Q.push({dist[1],1});

    while(!Q.empty()){
        int u = Q.top().second;
        Q.pop();

        if(!visited[u]){
            visited[u] = true;
            for(auto v : cost[u]) {
                if(dist[v.first] < min(dist[u], v.second)){
                    dist[v.first] = min(dist[u], v.second);

                    Q.push({dist[v.first], v.first});
                }
            }
        }
    }
}




void read(){
    in >> n >> m;
    cost.resize(n+1);
    dist.resize(n+ 1,0);
    for (int i = 1; i <= m; i++) {
        int x, y, c;
        in >> x >> y >> c;
        cost[x].push_back({y, c});
        cost[y].push_back({x, c});

    }

}

int main() {

    read();
    Dijkstra(dist, cost);

    out << dist[n];

    return 0;
}
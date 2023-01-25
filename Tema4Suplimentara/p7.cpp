#include <bits/stdc++.h>


using namespace std;

//ifstream in("maxflow.in");
//ofstream out("maxflow.out");
ifstream in("riremito.in");
ofstream out("riremito.out");

const int NMAX = 100005;

vector<pair<int, int>> adjList[NMAX];

long long int s_part[NMAX];
long long int dp[2][NMAX];

void dfs(int node, int father) {
    dp[0][node] = dp[1][node] = 0;

    long long int minim = INT64_MAX;
    for (auto it: adjList[node])
        if (it.first != father) {
            
            s_part[it.first] = s_part[node] + it.second;
            dfs(it.first, node);
            dp[1][node] += min(dp[1][it.first] + 2 * it.second, dp[0][it.first] + it.second + s_part[node]);

            if (dp[0][it.first] - min(dp[1][it.first] + it.second, dp[0][it.first] + s_part[node]) < minim)
                minim = dp[0][it.first] - min(dp[1][it.first] + it.second, dp[0][it.first] + s_part[node]);
        }

    if (minim < INT64_MAX)
        dp[0][node] = dp[1][node] + minim;
}

int main() {


    int x, y, z, n = 0, m = 0;

    in >> n;

    for (int i = 1; i < n; ++i) {
        in >> x >> y >> z;
        adjList[x].emplace_back(make_pair(y, z));
        adjList[y].emplace_back(make_pair(x, z));
    }


    in >> m;
    int node;
    while (m--) {
        in >> node;
        s_part[node] = 0;
        dfs(node, 0);
        out << dp[0][node] << '\n';
    }

    return 0;
}
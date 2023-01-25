#include <bits/stdc++.h>

using namespace std;

ifstream in("dbz.in");
ofstream out("dbz.out");



int n, m, dp[1505], p[1505];
vector<pair<int, int> > adjList[30005];
priority_queue<pair<int, int> > q;

int main() {
    in >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        in >> x >> y >> z;
        adjList[x].emplace_back(y, z);
        adjList[y].emplace_back(x, z);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            dp[j] = INT_MAX, p[j] = -1;
        dp[i] = 0;

        q.push({0, i});

        while (!q.empty()) {
            int node = q.top().second;
            int cost = q.top().first;
            q.pop();

            if (cost != -dp[node]) 
                continue;

            for (auto k: adjList[node]) {
                int v = k.first;
                int d = k.second;

                if (dp[v] > dp[node] + d) {
                    dp[v] = dp[node] + d;
                    p[v] = p[node];
                    q.push(make_pair(-dp[v], v));

                    if (node == i)
                        p[v] = v;
                }
            }
        }
        int ans = INT_MAX;
        for (int z = 1; z <= n; z++) {
            for (int j = 0; j < adjList[z].size(); j++) {
                int x = adjList[z][j].first;
                int cost = adjList[z][j].second;

                if ((p[x] == p[z]) || (i == z && p[x] == x) || (i == x && p[z] == z))
                    continue;
                ans = min(ans, cost + dp[z] + dp[x]);
            }
        }

        if (ans == INT_MAX)
            out << "-1 ";
        else
            out << ans << ' ';
    }

    return 0;
}
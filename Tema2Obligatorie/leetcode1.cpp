#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start, int end) {
        vector<pair<double, int>> adjList[n + 1];
        double prob[n + 1][n + 1];
        int k = 0;

        for (auto edg: edges) {
            adjList[edg[0]].emplace_back(succProb[k], edg[1]);
            adjList[edg[1]].emplace_back(succProb[k], edg[0]);
//            prob[edg[0]][edg[1]] = succProb[k];
            k++;
        }

        vector<double> dist(n + 5, 0);
        priority_queue<pair<double, int>> Q;
        Q.push(make_pair(0, start));
        dist[start] = 1;
        while (!Q.empty()) {
            int actNode = Q.top().second;
            double actProb = Q.top().first;
            Q.pop();
//            cout<<actNode << " "<< endl;
            for (auto el: adjList[actNode]) {
                int nNode = el.second;
                double nProb = el.first;
                if (dist[actNode] * nProb > dist[nNode]) {
                    dist[nNode] = dist[actNode] * nProb;
                    Q.push(make_pair(dist[nNode], nNode));
                }

            }

        }

        return dist[end];
    }
};

int main() {
    int n = 3;
    vector<vector<int>> edges = {{0,1}, {1,2}, {0,2}};
    vector<double> succProb = {0.5, 0.5, 0.3};
    int start = 0;
    int end = 2;
    cout<<Solution().maxProbability(n, edges, succProb, start, end);
    return 0;
}
//Kruskal pe graf, unde costul e distanta dintre oricare doua puncte(graf complet)
#include <iostream>
#include <bits/stdc++.h>

using namespace std;


class Solution {
private:
    static const int mx = 100005;
    int sets[mx];
    int ranks[mx];
public:
    int mDist(vector<int> &p1, vector<int> &p2) {
//        cout<< p1[0]<<" "<<p1[1]<<" - "<<p2[0]<<" "<<p2[1]<<" :" << abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])<<endl;
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
    }
;
    void uni(int x, int y) {
        if (ranks[x] > ranks[y])
            sets[y] = x;
        else
            sets[x] = y;
        if (ranks[x] == ranks[y])
            ranks[y]++;
    }


    int find(int x) {
        int repr = x, y;
        while (repr != sets[repr])
            repr = sets[repr];
        while (x != sets[repr]) {
            y = sets[x];
            sets[x] = repr;
            x = y;
        }
        return repr;
    }

    int minCostConnectPoints(vector<vector<int>> &points) {

        vector<tuple<int, int, int>> edges;
        // distantele dintre oricare 2 puncte
        for (int i = 0; i < points.size(); i++)
            for (int j = i + 1; j < points.size(); j++) {
                edges.emplace_back(make_tuple(mDist(points[i], points[j]), i, j));
            }
        sort(edges.begin(), edges.end());


        // Kruskal si adun in cost de fiecare data cand adaug o muchie
        int cost = 0;
        for (int i = 0; i < points.size(); i++) {
            sets[i] = i;
            ranks[i] = 1;
        }
        for (auto x: edges) {
            if (find(get<1>(x)) != find(get<2>(x))) {

                uni(find(get<1>(x)), find(get<2>(x)));
                cost += get<0>(x);
//                cout<<get<1>(x)<<" "<<get<2>(x)<< " :"<<get<0>(x)<< endl;
            }
        }
        return cost;
    }
};


int main() {
    vector<vector<int>> pp = {{0, 0},
                              {2, 2},
                              {3, 10},
                              {5, 2},
                              {7, 0}};
    vector<vector<int>> pp2 = {{0,0}, {1,1}, {1,0}, {-1,1}};
    cout << Solution().minCostConnectPoints(pp2);
    return 0;
}
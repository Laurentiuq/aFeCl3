#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        vector<int> adjList[5000];
        for(auto el: dislikes)
        {
            adjList[el[0]].push_back(el[1]);
            adjList[el[1]].push_back(el[0]);

        }
        return BFS(1, adjList, n);
    }

    bool BFS(int sNode, vector<int> adjList[], int& n){
        vector<int> colors(n+1, -1);

        for(int i = 1; i <= n; i++)
        {
            if(colors[i] == -1){
                colors[i] = 0;
                queue<int> q;
                q.push(i);
                while(!q.empty())
                {
                    int pc = q.front();
                    q.pop();
                    for(auto el: adjList[pc])
                    {
                        if(colors[el] == -1){
                            colors[el] = !colors[pc];
                            q.push(el);
                        }
                        else if(colors[el] == colors[pc])
                            return false;
                    }
                }
            }
        }
        return true;
    }

};


int main(){

    Solution s;
    return 0;
}
// Dijkstra plus numarul de stopuri, actualizam doar pentru muchiile pentru care ne permit numarul de stopuri

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<pair<int, int>> adjList[n + 1];
        for(int i = 0; i < flights.size(); i++)
            adjList[flights[i][0]].emplace_back(make_pair(flights[i][1], flights[i][2]));
        vector<int> dist(n  + 1, INT_MAX);
        dist[src] = 0;
        queue<tuple<int,int,int>> q;
        q.push(make_tuple(src, 0, 0));
        while(!q.empty()){
            tuple<int,int,int> currentNode = q.front();
            if(get<2>(currentNode) > k)
                break;
            int currentNodeN = get<0>(currentNode), currentNodePrice = get<1>(currentNode), currentNodeStops = get<2>(currentNode);


            // daca gasesc pentru nextNode o distanta mai mica decat cea gasita anterior(trecand prin currentNode)
            for(auto nextNode : adjList[currentNodeN]){

                if(dist[get<0>(nextNode)] > currentNodePrice + get<1>(nextNode)){
                    dist[get<0>(nextNode)] = currentNodePrice + get<1>(nextNode);
                    // adaug in coada nodul urmator impreuna cu distanta actuala pana la nod si numarul de opriri
                    q.push(make_tuple(get<0>(nextNode), dist[get<0>(nextNode)], currentNodeStops + 1));
                }
            }
            q.pop();
        }
        if(dist[dst] == INT_MAX)
            return -1;
        return dist[dst];
    }

};




int main() {
    int n = 5;
    vector<vector<int>> flights = {{1,2,10},{2,0,7},{1,3,8},{4,0,10},{3,4,2},{3,2,10},{0,3,3},{3,1,6},{2,4,5}};
    int src = 0;
    int dest = 4;
    int k = 1;
    cout<<Solution().findCheapestPrice(n,flights,src,dest,k);
    return 0;
}
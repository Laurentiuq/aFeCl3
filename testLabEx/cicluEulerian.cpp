// O(m*n) gasire nod de start
//O(m) - Algoritmul lui Hierholzer recusiv
// Cautam un nod cu gradul extern impar - daca exista il alegem ca nod de start
// Construim un ciclu incepand cu nodul de start ales
// Adaugam la ciclu muchii care nu apartin inca ciclului(facem asta eliminand din
// lista de adiacenta a unui nod, nodul corespunzator pentru muchia formata)
#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    unordered_map<int, queue<int>> adjList;
    vector<vector<int>> sol;
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        int dim = pairs.size();
        adjList.clear();
        //first - grad intern, second - grad extern
        unordered_map<int, pair<int, int>> degrees;
        // adaugam elemente in lista de adiacenta
        // si retinem gradul intern/extern
        for(auto el:pairs){
            adjList[el[0]].push(el[1]);
            degrees[el[0]].second++;
            degrees[el[1]].first++;
        }
        int sNode = -1;
        // daca un nod are gradul extern impar o sa fie nodul de pornire
        for(auto el:adjList){
            int cNode = el.first;
            if(degrees[cNode].second - degrees[cNode].first == 1)
                sNode = cNode;
        }
        // daca toate nodurile au grad extern par putem incepe de la orice nod
        if(sNode == -1)
            sNode = pairs[0][0];
        sol.clear();

        euler(sNode);
        reverse(sol.begin(), sol.end());
        return sol;
    }
    // parcurgem fiecare muchie si daca este parcursa o eliminam din graf
    // adica eliminam nodul din queue in aces caz (semana cu dfs)
    void euler(int cNode){
        queue<int>* cQueue = &adjList[cNode];
        while(!cQueue->empty()){
            int nNode = cQueue->front();
            cQueue->pop();
            euler(nNode);
            // adaugam muchiile parcurse in vectorul cu solutii
            sol.push_back({cNode, nNode});
        }

    }
};
int main()
{
//    vector<vector<int>> pairs = {{5,1},{4,5},{11,9},{9,4}};
    vector<vector<int>> pairs2 =  {{1,3},{3,2},{2,1}};
//    vector<vector<int>> pairs3 = {{1,2}, {1,3}, {2,1}};
    Solution s;
//    vector<vector<int>> sol = s.validArrangement(pairs);
    s.validArrangement(pairs2);
//    s.validArrangement(pairs3);
//    for(const auto& el :sol){
//        for(auto node : el)
//            cout<<node<<" ";
//        cout<<endl;
//    }
    return 0;
}


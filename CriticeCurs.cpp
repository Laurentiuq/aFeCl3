#include <bits/stdc++.h>

using namespace std;

vector<int> viz(5000,0);
vector<int> niv_min(5000,0);
vector<int> nivel(5000,0);
vector<int> adjList[5000];
queue<pair<int,int>> q;


void df(int i){
    viz[i] = 1;
    niv_min[i] = nivel[i];
    for(auto j : adjList[i]){
        if(viz[j]==0){//ij muchie de avanasare
            nivel[j] = nivel[i];
            q.push({i,j}); // muchie din componenta biconexa
            df(j);
            niv_min[i] = min(niv_min[i], niv_min[j]);
            if(niv_min[j] > nivel[i]){
                //ij muchie critica
            }
            if(niv_min[j] >= nivel[i]){// i punct critic
                // eliminam din coada muchiile din componenta biconexa
                auto n1n2 = q.front();
                q.pop();
//                cout<<n1n2.first;
//                cout<<n1n2.second;
            }

        }
        else if (nivel[j] < nivel[i] - 1){
            niv_min[i] = min(niv_min[i], nivel[j]);
            q.push({i,j});
        }

    }
}

int main(){

    return 0;
}
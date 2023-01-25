#include <iostream>
#include <bits/stdc++.h>

using namespace std;
ifstream in("graf.in");
ofstream out("graf.out");


const int N = 7505;

vector<int> adjList[N];
int n, m, x, y;

void BFS(int node, vector<int> &dist){
    queue<int> Q;
    dist[node] = 0;
    Q.push(node);
    while(!Q.empty()){
        int currentNode = Q.front();
        Q.pop();
        for(auto nextNode: adjList[currentNode]) {
            if (dist[nextNode] == -1) {

                Q.push(nextNode);
                dist[nextNode] = dist[currentNode] + 1;
            }
        }
    }
}


int main(){
    in>>n>>m>>x>>y;
    int n1, n2;
    vector<int> distX(N, -1), distY(N, -1), nrDist(N, 0);
    int nrNoduri = n; // numarul de noduri care se afla pe toate lanturile minime
    int minDist;
    vector<int> noduriFinal(N, 1);
    for(int i = 0; i < m; i++){
        in>>n1>>n2;
        adjList[n1].push_back(n2);
        adjList[n2].push_back(n1);
    }

    BFS(x, distX);
    BFS(y, distY);
    minDist = distX[y];
    for(int i = 1; i <= n; i++) {
        if (distX[i] + distY[i] == minDist)
            // cate noduri se afla la o anumita distanta(distX[i]) de x si y pe un lant minim
            nrDist[distX[i]]++;
        // daca nu ne aflam pe un lant minim eliminam nodurile care se nu se afla pe un lant minim
        else {
            distX[i] = 0;
            noduriFinal[i] = 0;
            nrNoduri --;
        }
    }

    // daca sunt mai multe noduri la o anumita distanta inseamna ca nodurile aflate
    // la respectiva distanta nu apar pe toate lanturile minime
    for(int i=1; i<=n; i++)
        if(nrDist[distX[i]] > 1) {
            noduriFinal[i] = 0;
            nrNoduri--;
        }
    out<<nrNoduri<<endl;
    for(int i=1; i<=n; i++)
        if(noduriFinal[i])
            out<<i<<" ";
    return 0;
}
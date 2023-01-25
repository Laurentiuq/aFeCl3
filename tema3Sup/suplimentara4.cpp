// Problema cuplaj maxim, avem numere pare in dreapta, impare in stanga
// adaugam muchie doar intre cele care adunate dau un numar prim
// trebuie eliminate cele care au fost nevizitate si sunt pare, sau cele vizitate si sunt impare
// O(n^2) -- O(n * t), t flux maxim
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
ifstream in("maxflow.in");
ofstream out("maxflow.out");

int v[200005];
vector<int> adjList[20005];
unordered_map<int, int> cap[20005];
unordered_map<int,int> sol;
int prime[200005];
vector<bool> visited(200005, false);

int n;

void sieveEratostene(){
    for(int i = 2; i <= 200005; i++)
        prime[i] = 1;
    for(int i = 2; i * i <= 200005; i++)
        if(prime[i])
            for(int j = i * i; j <= 200005; j = j + i)
                prime[j] = 0;
}

void read(){
    cin >> n;
//    adjList.resize(n + m + 3);
//    cap.resize(n + m + 3, vector<int>(n + m + 3, 0));

    // numerele pare in stanga(se conecteaza cu nodul s = 0)
    for(int i = 1; i <= n; i++)
    {
        cin >> v[i];
        if(v[i]%2 == 0)
        {
            adjList[0].emplace_back(i);
            adjList[i].emplace_back(0);
            cap[0][i] = 1;
        }
        // numerele impare in drepta(se conecteaza cu nodul final = n + 1)
        else
        {
            adjList[i].emplace_back(n + 1);
            adjList[n+1].emplace_back(i);
            cap[i][n+1] = 1;
        }
    }

    // avem muchie intre numerele a caror suma este nr prim
    for(int i = 1; i <= n; i++)
    {
        for(int j = i + 1; j <=n;j++) {
            if (prime[v[i] + v[j]]) {
                adjList[i].emplace_back(j);
                adjList[j].emplace_back(i);
            }
            if (v[i] % 2 == 0)
                cap[i][j] = 1;
            else
                cap[j][i] = 1;
        }
    }
}

int BFS(int source, int dest, vector<int>& parent)
{
    fill(parent.begin(), parent.end(), -1);
    fill(visited.begin(), visited.end(), false);
    parent[source] = 0;
    visited[source] = true;
    queue<int> q;
    q.push(source);
    while(!q.empty()) {

        int pNode = q.front(); //nodul parinte
        q.pop();
        for (auto el: adjList[pNode])
        {
            int cNode = el; // copiii nodului parinte actual
            if(cNode != pNode && !visited[cNode] && cap[pNode][cNode] > 0)
            {
                parent[cNode] = pNode;

                if(cNode == dest)
                {
                    return 1;
                }
                visited[cNode] = true;
                //adaugam urmatorul nod ce urmeaza sa fie vizitat
                q.push({cNode});
            }
        }
    }

    return 0;
}


int FordFulkerson(int source, int dest)
{
    vector<int> parent(n + 3, -1);
    int mxFlow = 0;


    while(BFS(source,dest,parent)) {

        for (auto el: adjList[dest]) {
            if (parent[el] != -1) {
                int mnCap = INT_MAX;
                int cNode = dest;
                parent[dest] = el;
                while (cNode != source) {
                    mnCap = min(mnCap, cap[parent[cNode]][cNode]);
                    cNode = parent[cNode];
                }
                cNode = dest;
                while (cNode != source){
                    cap[cNode][parent[cNode]] += mnCap;
                    cap[parent[cNode]][cNode] -= mnCap;
                    cNode = parent[cNode];
                }
                mxFlow += mnCap;
            }
        }
    }
    return mxFlow;
}

int main()
{
    // precalculam care numere sunt prime
    sieveEratostene();
    read();
    out<<FordFulkerson(0, n + 1)<<endl;
    vector<int> ans;
    //trebuie eliminate cele care nu au fost vizitate si sunt pare, sau cele vizitate si sunt impare(pe ultimul drum de crestere)
    for(int i = 1; i<=n;i++)
        if((visited[i] && v[i]%2==1) || (!visited[i] && v[i]%2==0))
            ans.emplace_back(v[i]);
    cout<<ans.size()<<endl;
    for(auto el:ans)
        cout<<el<<" ";

    return 0;
}
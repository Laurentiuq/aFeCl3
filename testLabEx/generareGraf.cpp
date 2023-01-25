// Algoritmul de flux, adauga un nod de start si un nod final
// Capacitatea pe muchii o sa fie gradul de iesire pe muchiile care pleaca din start si 
// gradul de intrare pe muchiile spre nodul final
// O(m*L)

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
using namespace std::chrono;
//ifstream in("maxflow.in");
//ofstream out("maxflow.out");
ifstream in("harta.in");
ofstream out("harta.out");
vector<vector<int>> adjList;
vector<pair<int,int>> degrees;
unordered_map<int, int> cap[205];
unordered_map<int,int> sol;
vector<int> parents;
struct muchie{

};
int n,m,e;
void read(){
    in >> n;
    adjList.resize(2 * n + 2);
//    cap.resize(n + m + 3, vector<int>(n + m + 3, 0));
    int x, y;
    degrees.emplace_back(make_pair(0,n));
    while(in>>x>>y){
        degrees.emplace_back(make_pair(x,y));
    }

    for(int i = 1; i <= n ;i++)
        for(int j = n + 1; j<= n * 2; j++)
        {
            if(i + n != j){
                adjList[i].emplace_back(j);
                adjList[j].emplace_back(i);
                cap[i][j]++;
            }
        }

    for(int i = 1; i <= n; i++)
    {
        adjList[0].emplace_back(i);
//        adjList[i].emplace_back(0);
        cap[0][i] = degrees[i].first;
    }
    for(int i = 1; i + n <= n * 2; i++)
    {
        adjList[i + n].emplace_back(n * 2 + 1);
        adjList[n * 2 + 1].emplace_back(i + n);
        cap[i + n][n * 2 + 1] = degrees[i].second;
    }



}

int BFS(int source, int dest, vector<int>& parent)
{

    fill(parent.begin(), parent.end(), -1);
    parent[source] = 0;
    queue<int> q;
    q.push(source);
    while(!q.empty()) {

        int pNode = q.front(); //nodul parinte
        q.pop();
        for (auto el: adjList[pNode])
        {
            int cNode = el; // copiii nodului parinte actual
            if(cNode != pNode && parent[cNode] == -1 && cap[pNode][cNode] > 0)
            {
                parent[cNode] = pNode;
                if(cNode == dest)
                {

                    return 1;
                }
                //adaugam urmatorul nod ce urmeaza sa fie vizitat
                q.push({cNode});
            }
        }
    }
    return 0;
}


int FordFulkerson(int source, int dest)
{
    vector<int> parent(n * 2 + 2, -1);
    parent[source] = -2;
    int mxFlow = 0;


    while(BFS(source,dest,parent)) {

        for (auto el: adjList[dest]) {
            if (parent[el] != -1) {
                int mnCap = INT_MAX;
                int cNode = dest;
//                parent[dest] = el;
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

    auto start = high_resolution_clock::now();
    read();

    out<<FordFulkerson(0, 2*n+1)<<endl;
    for(int i = 1; i<=n;i++)
        for(int j = n + 1; j<= n * 2; j++){
            if(i + n != j && cap[i][j] == 0)
                out<<i<<" "<<j - n<<endl;
        }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Durata: "<< duration.count();
    return 0;
}






//V2
// Acelasi algoritm dar fara sa retinem muchiile sub forma de pozitii in lista de adiacenta,
// Avem doar o lista de adiacenta normala
// 90 de puncte cu unordered_map
/*
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
using namespace std::chrono;
//ifstream in("maxflow.in");
//ofstream out("maxflow.out");
ifstream in("cuplaj.in");
ofstream out("cuplaj.out");
vector<int> adjList[20005];
unordered_map<int, int> cap[20005];
unordered_map<int,int> sol;
struct muchie{

};
int n,m,e;
void read(){
    in >> n >> m >> e;
//    adjList.resize(n + m + 3);
//    cap.resize(n + m + 3, vector<int>(n + m + 3, 0));
    int x, y;
    for(int i = 0; i < e; i++)
    {
        in >> x >> y;
        adjList[x].emplace_back(y+n);
        adjList[y + n].emplace_back(x);
        cap[x][y+n] = 1;
    }
    for(int i = 1; i <= n; i++)
    {
        adjList[0].emplace_back(i);
//        adjList[i].emplace_back(0);
        cap[0][i] = 1;
    }
    for(int i = 1; i <= m; i++)
    {
        adjList[i + n].emplace_back(n + m + 1);
        adjList[n + m + 1].emplace_back(i + n);
        cap[i + n][n+m+1] = 1;
    }
}

int BFS(int source, int dest, vector<int>& parent)
{

    fill(parent.begin(), parent.end(), -1);
    parent[source] = 0;
    queue<int> q;
    q.push(source);
    while(!q.empty()) {

        int pNode = q.front(); //nodul parinte
        q.pop();
        for (auto el: adjList[pNode])
        {
            int cNode = el; // copiii nodului parinte actual
            if(cNode != pNode && parent[cNode] == -1 && cap[pNode][cNode] > 0)
            {
                parent[cNode] = pNode;
                if(cNode == dest)
                {

                    return 1;
                }
                //adaugam urmatorul nod ce urmeaza sa fie vizitat
                q.push({cNode});
            }
        }
    }
    return 0;
}


int FordFulkerson(int source, int dest)
{
    vector<int> parent(n + m + 3, -1);
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
                    if(cap[parent[cNode]][cNode] == 0 && parent[cNode] != 0  && cNode != n + m + 1)
                        sol[parent[cNode]] = cNode - n;
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

    auto start = high_resolution_clock::now();
    read();

    out<<FordFulkerson(0, n + m + 1)<<endl;



    for(int i = 1; i <= n; i++)
    {
        if(sol[i] != 0 && i != 0 && sol[i] != n + m + 1)
        out<< i << " "<<sol[i]<<endl;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Durata: "<< duration.count();
    return 0;
}
*/
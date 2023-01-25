// Folosind algoritmul pentru flux, adaugam un nod de inceput, un nod de final si capacitate 1 pe muchii
// Retinem muchiile sub forma de pozitii in lista de adiacent, pentru a avea acces rapid la nodurile adiacente
// retinem pentru fiecare muchie capacitatea, pozitia din lista de adiacenta, nodurile pe care le uneste
//O(m*L)
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;
//ifstream in("maxflow.in");
//ofstream out("maxflow.out");
ifstream in("cuplaj.in");
ofstream out("cuplaj.out");
struct edge{
    int n1, n2, cap, pos;
};
vector<vector<int>> adjList;
vector<edge> edges;
vector<bool> visited;
vector<int> parent;
int n,m,e, nrN;
int source,dest;
void addEdge(int x, int y){
    int dim = (int)edges.size();

    adjList[x].push_back(dim);
    adjList[y].push_back(dim+1);

    edges.push_back({x,y,1,dim+1});
    edges.push_back({y,x,0, dim});
}
void read(){
    in >> n >> m >> e;
    nrN = n + m + 2;
    source = 0;
    dest = nrN -1;
    adjList.resize(nrN);
    int x, y;
    for(int i = 0; i < e; ++i)
    {
        in >> x >> y;
        addEdge(x,y + n);

    }
    for(int i = 1; i <= n; ++i)
    {
        addEdge(0,i);


    }
    for(int i = 1; i <= m; ++i)
    {
        addEdge(i+n, m + n + 1);

    }
}

bool BFS()
{

    parent.clear();
    parent.resize(nrN);
    visited.clear();
    visited.resize(nrN, false);

    visited[source] = true;
    queue<int> q;
    q.push(source);
    while(!q.empty()) {

        int pNode = q.front(); //nodul parinte
        q.pop();
        if(pNode != dest)
            // alegem noduri adiacente cu nodul parinte(nodul (0) de start in primul rand)
            for (int el: adjList[pNode])
            {
                // muchia care pleaca din nodul el
                edge cEdge = edges[el];
                // daca nodul in care ajunge muchia din 'el' nu a fost cuplat
                // si mai putem sa trimitem flux, o cuplam cu 'el'
                if(!visited[cEdge.n2] && cEdge.cap != 0)
                {
                    parent[cEdge.n2] = el;
                    //adaugam urmatorul nod ce urmeaza sa fie vizitat
                    q.push(cEdge.n2);
                    visited[cEdge.n2] = true;
                }
            }
    }
    return visited[dest];
}


int FordFulkerson(int source, int dest)
{
    int mxFlow = 0;


    while(BFS()) {
        for (int el: adjList[dest]) {
            // daca nodul in care ajunge muchia ce pleaca din 'el'
            // a fost vizitat si muchia de intoarcere poate intoarce flux
            if (visited[edges[el].n2] && edges[edges[el].pos].cap != 0) {
                int mnCap = INT_MAX;
                edge cEdge = edges[el];
                parent[dest] = cEdge.pos;
                int cNode = dest;
                // parcurgem drumul de crestere de la destinatie spre sursa
                while (cNode != source) {
                    mnCap = min(mnCap, edges[parent[cNode]].cap);
                    // mergem in nodul dinspre care a venit muchia
                    cNode = edges[parent[cNode]].n1;
                }
                cNode = dest;
                while (cNode != source){
                    // pentru muchia reziduala crestem fluxul
                    // muchia de pe pozitia parintelui nodului curent
                    edges[edges[parent[cNode]].pos].cap += mnCap;
                    // pentru muchia normala scadam capacitatea ocupata
                    edges[parent[cNode]].cap -= mnCap;
                    cNode = edges[parent[cNode]].n1;
                }
                mxFlow += mnCap;
            }
        }
    }
    return mxFlow;
}

int main() {



    auto start = high_resolution_clock::now();

    read();

    out << FordFulkerson(0, n + m + 1) << endl;

    for(auto edge:edges){
        if(edge.n1 < edge.n2 && edge.n1 != 0 && edge.n2!= dest && edge.cap == 0)
            out<<edge.n1<<" "<<edge.n2 - n<<endl;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Durata: " << duration.count();
    return 0;
}
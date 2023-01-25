#include <iostream>
#include <bits/stdc++.h>

using namespace std;

ifstream in("lesbulan.in");
ofstream out("lesbulan.out");


const int N = 55;
// lista de adiacenta
vector<vector<int>> adjList;
vector<bool> visited;
int n, m, t;
bool cycle;

// citirea datelor + alocare de spatiu
void read() {
    in >> n >> m;
    int x, y;
    cycle = false;
    adjList.clear();
    visited.clear();
    visited.resize(n + 1, false);
    adjList.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        in >> x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }
}

// DFS pentru a verifica daca exista un ciclu
void dfsCycle(int node, int parent) {
    visited[node] = true;
    for (int nextNode: adjList[node]) {
        if (visited[nextNode] && nextNode != parent) {
            cycle = true;
        }
        if (!visited[nextNode]) {
            dfsCycle(nextNode, node);
        }

    }
}

// sterge frunzele pentru fiecare componenta conexa care este arbore
void removeLeaves() {
    vector<int> leaves;
    // frunzele
    for (int i = 1; i < adjList.size(); i++) {
        if (adjList[i].size() == 1)
            leaves.push_back(i);
    }
    // stergem frunzele din listele de adiacenta ale nodurilor parinte
    // apoi stergem efectiva frunza
    for (int i: leaves) {
        if (!adjList[i].empty()) {
            adjList[adjList[i][0]].erase(find(adjList[adjList[i][0]].begin(), adjList[adjList[i][0]].end(), i));
            adjList[i].clear();
        }
    }
    leaves.clear();
}

int main() {
    in >> t;
    while (t--) {
        bool ok = true;
        read();
        // daca are cicluri in vreo componenta conexa nu exista o solutie
        for (int i = 1; i < adjList.size(); i++) {
            if (!visited[i])
                dfsCycle(i, i);
            if (cycle)
                ok = false;
        }
        // daca fiecare componenta conexa e arbore(nu am gasit cicluri), stergem frunzele de doua ori si daca in urma procesului mai raman noduri
        // cu gradul mai mare ca 2 atunci nu exista solutie
        if(ok) {
            removeLeaves();
            removeLeaves();
            for (const auto &el: adjList) {
                if (el.size() > 2)
                    ok = false;
            }
        }
        out << ok << endl;
    }

    return 0;
}
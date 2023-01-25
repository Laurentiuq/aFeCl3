/* 
	Programul foloseste algoritmul lui Tarjan pentru determinarea componentelor tare conexe
	Complexitate  = O(n + m)
*/

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

ifstream in("ctc.in");
ofstream out("ctc.out");


int n, m;
vector<list<int>> adjList;
vector<int> indexes(100005, -1); //momentul la care este descoperit in DFS
vector<int> lowlinks(100005, -1); // indexul celui mai mic nod la care exista drum
vector<bool> stackStatus(100005, false); // pentru a retine daca un nod se afla sau nu pe stack
list<int> st; // stack-ul pe care se retin nodurile din componentele tare conexe
int nrComponents = 0;
list<list<int>> connectedComponents; // vor fi retinute la final componentele tare conexe
int ind = 0;

// DFS pe care se aplica si algoritmul lui Tarjan
void DFS(int node) {
    indexes[node] = ind;
    lowlinks[node] = ind; 
    st.push_back(node); 
    stackStatus[node] = true; 
    ind += 1;
	// pentru fiecare vecin daca nu a mai fost vizitat apelam DFS(vecin) pentru a-i atribui un index si un lowlink
	// iar daca e vizitat alegem minimul dintre lowlink-ul vecinilor si nodului( daca exista drum de la vecin la 
	// un nod cu index mai mic atunci exista si de la nodul parinte la cel cu index mai mic)
    for (auto vecin: adjList[node]) {
        if(indexes[vecin] == -1){
            DFS(vecin);
            lowlinks[node] = min(lowlinks[node], lowlinks[vecin]);
        }
        else if(stackStatus[vecin])
            lowlinks[node] = min(lowlinks[node], indexes[vecin]);
    }
	
	// daca nodul lowlink-ul nodului actual este egal cu indexul sau atunci
	// nodul curent inchide o componenta tare conexa
    if (lowlinks[node] == indexes[node]){
        list<int> currentComponents;
        nrComponents++;
        int el = -1;
		// pana cand se ajunge inapoi la nodul de la care am plecat
        while(node != el){
            el = st.back();
            st.pop_back();
            currentComponents.push_back(el);
            stackStatus[el] = false;
        }
        connectedComponents.push_back(currentComponents);
    }
}

int main() {

    // crearea listei de adiacenta
    in >> n >> m;
    adjList.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int p1, p2;
        in >> p1 >> p2;
        adjList[p1].push_back(p2);
    }

    // afisarea listei de adiacenta
//    for (int j = 1; j <= n; j++) {
//        printf("%d:", j);
//        for (auto el: adjList[j])
//            printf("%d, ", el);
//        printf("\n");
//    }
    for(int node = 1; node <= n; node ++)
        if (indexes[node] == -1)
            DFS(node);
//    DFS(2);
    out<<nrComponents<<endl;
    while (!connectedComponents.empty()) {
        list<int> component = connectedComponents.back();
        connectedComponents.pop_back();
        while(!component.empty()) {
            out << (component.back())<<" ";
            component.pop_back();
        }
        out<<endl;
    }
    return 0;
}

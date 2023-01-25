// Algoritmul lui Kruskal aplicat de n-k ori, pentru ca astfel ne creaza k componente conexe, exact numarul de clase de care avem nevoie
// 

#include <iostream>
#include <bits/stdc++.h>


using namespace std;

vector<string> words;  // cuvintele
int k; // numarul de clustere


// calculeaza si returneaza distanta Levenshtein dintre doua cuvinte
int distLev(string &c1, string &c2) {
    vector<vector<int>> dist;
    int ln_c1 = c1.length();
    int ln_c2 = c2.length();
    dist.resize(ln_c1 + 1, vector<int>(ln_c2 + 1));
    dist[0][0] = 0;
    for (int i = 1; i <= ln_c1; i++)
        dist[i][0] = i;
    for (int j = 1; j <= ln_c2; j++)
        dist[0][j] = j;
    for (int i = 1; i <= ln_c1; i++) {
        for (int j = 1; j <= ln_c2; j++) {
            if (c1[i - 1] != c2[j - 1])
                dist[i][j] = 1 + min(min(dist[i - 1][j], dist[i][j - 1]), dist[i - 1][j - 1]);
            else
                dist[i][j] = dist[i-1][j-1];
        }
    }
    return dist[ln_c1][ln_c2];
}


// citeste cuvintele si le adauga intr-un vector
void read(){
    fstream fin;
    fin.open("ctc.in");
    string word;
    while(fin >> word)
        words.push_back(word);
//    for(int i = 0; i<words.size(); i++)
//        cout<<words[i]<<endl;
}


// Union find
const int mx = 100005;
int sets[mx], ranks[mx];
void uni(int x, int y){
    // radacina arborelui mai mare(inalt) devine parinte pentru radacina celuilalt arbore
    if(ranks[x] > ranks[y])
        sets[y] = x;
    else
        sets[x] = y;
    // daca arborii au aceeasi inaltime crestem inaltimea cu 1
    if (ranks[x] == ranks[y])
        ranks[y]++;
}

int find(int x){
    int repr = x, y;
    // gasim reprezentantul unei multimi(radacina arborelui)
    while(repr != sets[repr])
        repr = sets[repr];
    // setam pentru toti membrii multimii radacina drept reprezentant
    while(sets[repr] != x)
    {
        y = sets[x];
        sets[x] = repr;
        x = y;
    }
    return repr;
}

void cluster() {
    // vector cu trei-tuplu de forma <cost, muchie1, muchie2>
    vector<tuple<int, int, int>> edges;
    int distsLev[words.size()][words.size()];
    // pentru fiecare cuvant calculam distanta fata de celelalte cuvinte si le adaugam in vector
    for (int i = 0; i < words.size(); i++) {
        sets[i] = i;
        for (int j = i + 1; j < words.size(); j++) {
            distsLev[i][j] = distLev(words[i], words[j]);
            distsLev[j][i] = distsLev[i][j];
            edges.emplace_back(distsLev[i][j], i, j);
        }
    }

    // sortam dupa distanta cea mai mica
    sort(edges.begin(), edges.end());

    // Kruskal
    int nr_pasi = 0; // retinem numarul de pasi, vrem doar n-k pasi pentru a ramane k componente conexe
    for (auto el: edges) {
		nr_pasi++;
        if (find(get<2>(el)) != find(get<1>(el))){
            uni(find(get<2>(el)), find(get<1>(el)));
			
		}
        if (nr_pasi > words.size() - k)
            break;
    }



    ofstream fout;
    fout.open("ctc.out");
    // vector in care marcam doar nodurile care raman ca reprezentanti
    vector<int> repr(words.size(), 0);
    // gradul de separare
    int grad_sep = INT_MAX;
    for (int i = 0; i < words.size(); i++)
        repr[sets[i]] = 1;
    for (int i = 0; i < repr.size(); i++)
        // daca am ajuns la un reprezentatn afisam toate cuvintele care fac parte din multimea reprezentantului
        if (repr[i]) {
            for (int j = 0; j < words.size(); j++) {
                if (sets[j] == i) {
                    fout << words[j] << " ";
                }
            }
            fout << endl;
        }

    // pentru fiecare doua cuvinte din multimi diferite(au repr. diferit) alegem distanta minima

    for (int i = 0; i < words.size(); i++)
        for (int j = i + 1; j < words.size(); j++)
        {
            if(sets[i] != sets[j])
                grad_sep = min(grad_sep, distsLev[i][j]);
        }

    fout<<grad_sep<<endl;
}

int main() {
    read();
    cluster();
    return 0;
}
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

//ifstream in("ctc.in");
//ofstream out("ctc.out");

ifstream in("disjoint.in");
ofstream out("disjoint.out");

const int mx = 100005;

int n, m, cod, x, y;
int sets[mx];
int ranks[mx];


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

int main() {
    in >> n >> m;
    for (int i = 1; i <= n; i++) {
        sets[i] = i;
        ranks[i] = 1;
    }


    for (int i = 1; i <= m; i++)
    {
        in>>cod>>x>>y;
        // unesc multimile dupa reprezentanti
        if(cod == 1){
            uni(find(x), find(y));
        }
        if(cod == 2){
            if(find(x) == find(y))
                out<<"DA\n";
            else
                out<<"NU\n";
        }
    }
    return 0;
}
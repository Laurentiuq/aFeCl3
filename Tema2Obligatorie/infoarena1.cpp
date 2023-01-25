
/* Tratam centralele ca pe un singur nod in graf, calculam distanta de la fiecare bloc(nod) la cea mai aporpiata
 * centrala. Folosind algoritmul lui Prim alegem cea mai mica distanta dintre nodul centralelor si nodurile blocurilor.
 */

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

ifstream in("retea2.in");
ofstream out("retea2.out");


const int N = 2005;
const int M = 2005;


int n, m;
vector<pair<int, int>> centrale, blocuri;
vector<double> distantaCentrala; // distanta fiecarui nod pana la cea mai apropiata centrala
double finalDistance; // distanta totala la final
vector<bool> decided; // daca am decis pentru un nod care este distanta pe care o vom alege
vector<double> finalDistances; // distantele finale alese pentru a obtine APCM

double dist(pair<int, int> source, pair<int, int> dest) {
    return sqrt((pow(source.first - dest.first, 2)) + pow((source.second - dest.second), 2));

}

void read() {
    // alocare spatiu + citire
    in >> n >> m;
    distantaCentrala.resize(m + 1, INT_MAX);
    decided.resize(m + 1, false);
    finalDistances.resize(m + 1, INT_MAX);
    int x, y;
    for (int i = 0; i < n; i++) {
        in >> x >> y;
        centrale.emplace_back(x, y);
    }
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        blocuri.emplace_back(x, y);
    }

    // calculam distanta de la fiecare bloc la cea mai apropiata centrala de el
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            distantaCentrala[i] = min(distantaCentrala[i], dist(blocuri[i], centrale[j]));
        finalDistances[i] = distantaCentrala[i];
    }


}


int main() {
    read();

    for (int i = 0; i < blocuri.size(); i++) {
        double actDist = INT_MAX;
        int lastChosen = -1;
        // pentru fiecare nod care nu a fost ales il legam de cel mai apropiat nod deja ales
        // initial se considera ales nodul centralelor pentru ca finalDistances retine distantele minime
        // corespunzatoare centrala-bloc
        {
            for (int j = 0; j < blocuri.size(); j++) {
                if (!decided[j]) {
                    if (finalDistances[j] < actDist) {
                        actDist = finalDistances[j];
                        lastChosen = j;
                    }
                }
            }
        }
        // actualizam distanta finala
        finalDistance += actDist;
        // Calculam distantele de la ultimul nod ales la celelalte noduri.
        // Modificam finalDistances cu minimul dintre valorile existente si cele noi calculate astfel incat la urmatorul
        // pas vom alege cea mai mica distanta dintre un nod nevizitat la unul vizitat.
        for (int j = 0; j < blocuri.size(); j++)
            finalDistances[j] = min(finalDistances[j], dist(blocuri[j], blocuri[lastChosen]));
        decided[lastChosen] = true;
    }
    out << fixed << setprecision(6) << finalDistance;
    return 0;
}
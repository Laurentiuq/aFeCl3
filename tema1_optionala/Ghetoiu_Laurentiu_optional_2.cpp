#include <iostream>
#include <bits/stdc++.h>

/*
 * Algoritmul lui Lee
 */

using namespace std;

const int N = 1005, M = 1005;
int di[] = {-1, 0, 1, 0};
int dj[] = {0, 1, 0, -1};
//vector<vector<int>> matr(N, vector<int> (N)), cost(N, vector<int> (N));
int matr[N][N], cost[N][N];
deque <pair <int, int>> Q;

ifstream in("padure.in");
ofstream out("padure.out");


int n, m, pa, ca, pc, cc;


int main() {
    in >> n >> m >> pa >> ca >> pc >> cc;
    // -1 la fiecare pentru index de la 0
    pa--;
    ca--;
    pc--;
    cc--;
//    cout << n << " " << m << " " << pa << " " << ca << " " << pc << " " << cc<<endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            in >> matr[i][j];
            cost[i][j] = INT_MAX; // initial consideram distanta maxima
        }


//    for(int i = 0; i < n; i++){
//        for(int j = 0; j < m; j++)
//            cout<<matr[i][j]<<" ";
//        cout<<endl;
//    }


    // adaugam in coada punctul de start
    Q.emplace_back(pa, ca);
    cost[pa][ca] = 0;
    // cat timp mai avem elemente in coada
    while (!Q.empty()){

        int currentI, currentJ, diamant, nextI, nextJ;
        currentI = Q.front().first;
        currentJ = Q.front().second;
        Q.pop_front();

        // pentru fiecare vecin din S,N,E,V
        for(int i=0; i < 4; i++){
            // indicii vecinilor
            nextI = currentI + di[i];
            nextJ = currentJ + dj[i];
            // daca se incadreaza in matrice
            if(nextI >= 0 && nextI < n && nextJ >= 0 && nextJ < m) {
//                printf("nextI: %d, nextJ: %d\n", nextI, nextJ);
                // daca tipurile de arbori difera(valorea vecinului e diferita de cea curenta)
                // atunci creste costul cu 1
                diamant = 0;
                if (matr[currentI][currentJ] != matr[nextI][nextJ])
                    diamant = 1;

                // dintre vecini ii alegem pe cei care ne ofera un cost mai mic decat cel pe care l-am mai obtinut
                if(cost[currentI][currentJ] + diamant < cost[nextI][nextJ]) {
                    cost[nextI][nextJ] = cost[currentI][currentJ] + diamant;
                    // daca vecinul cu cel mai mic cost necesita cresterea costului atunci il adaugam la final
                    // pentru ca exista sansa sa gasim un drum mai bun de la valorile deja aflate inaintea lui in Q
                    // daca nu necesita cresterea costului ii acordam prioritate deoarece exista o sansa mai mare
                    // sa ne ofere cel mai mic cost
                    if (diamant)
                        Q.emplace_back(pair<int, int>(nextI, nextJ));
                    else
                        Q.emplace_front(pair<int, int>(nextI, nextJ));
                }
            }
        }
    }


//    cout<<endl;
//    for(int i = 0; i < n; i++){
//        for(int j = 0; j < m; j++)
//            cout<<cost[i][j]<<" ";
//        cout<<endl;
//    }

    out<<cost[pc][cc];

    return 0;
}



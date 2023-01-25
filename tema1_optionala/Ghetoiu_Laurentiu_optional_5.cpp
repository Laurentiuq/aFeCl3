#include <iostream>
#include <bits/stdc++.h>

using namespace std;

ifstream in("ctc.in");

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>> &grid) {
        int area_max = 0;
        unsigned int m = grid.size();
        unsigned int n = grid[0].size();
        vector<vector<int>> visited(m, vector<int>(n, 0));
        int di[] = {0, -1, 0, 1};
        int dj[] = {-1, 0, 1, 0};
        // parcurgem toata matricea si daca gasim 1 pe o pozitie incepem un BFS de pe pozitia respectiva
        // cat timp putem aplica BFS (mai gasim vecini cu 1) crestem aria curenta cu 1
        for(int i= 0; i<m; i++)
            for(int j = 0; j<n; j++)
            {
                // daca am gasit o pozitie cu 1 BFS pt pozitia respectiva
                if(!visited[i][j] && grid[i][j] == 1){
                    queue<pair<int,int>> q;
                    q.push({i,j});
                    visited[i][j] = 1;
                    int curent_area = 0;
                    int nextI, nextJ, cI, cJ;
                    while(!q.empty()){
                        curent_area++;
                        cI = q.front().first;
                        cJ = q.front().second;
                        q.pop();
                        // pentru vecinii de sus, jos, stanga, dreapta
                        for(int k = 0; k<4; k++){
                            nextI = cI + di[k];
                            nextJ = cJ + dj[k];
                            // daca indicii vecinilor se incadreaza in matrice, pozitia are valoarea 1 si nu a mai fost vizitata
                            // atunci o putem adauga in coada
                            if(nextI >= 0 && nextI < m && nextJ >= 0 && nextJ < n && grid[nextI][nextJ] == 1 && !visited[nextI][nextJ]) {
                                visited[nextI][nextJ] = 1; // il marcam aici ca vizitat pentru a nu mai verifica daca avem duplicate
                                q.push({nextI, nextJ});
                            }
                        }
                    }
                    if(curent_area > area_max)
                        area_max = curent_area;
                }
            }
        return area_max;
    }

};


int main() {
    vector<vector<int>> v(8, vector<int>(13));
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 13; j++){
            in >> v[i][j];
            }
    cout<<Solution().maxAreaOfIsland(v);
}
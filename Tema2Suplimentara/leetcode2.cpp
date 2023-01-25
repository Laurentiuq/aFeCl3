
// Sortam queries si muchii si pentru fiecare query aplicam union-find cat timp costul muchiei actuale
// e mai mic decat cel din query, daca am ajuns la o muchie cu cost mai mare verifcam daca cele doua noduri
// din query au acelasi reprezentant - daca da exista drum cu muchii sub acel cost, altfel nu exista
// adaugam in sol pe pozitia corespunzatoare raspunsul
// trecem la urmatorul query
// pentru fiecare query mai adaugam si al catelea query e pentru a nu strica ordinea din solutie dupa ce sortam
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    vector<int> sets, ranks;
public:
    static bool comp(vector<int>& x1, vector<int>& x2){
        return x1[2] < x2[2];
    }

    void uni(int x, int y){
        if(ranks[x] > ranks[y])
            sets[y] = x;
        else
            sets[x] = y;
        if(ranks[x] == ranks[y])
            ranks[y]++;
    }

    int find(int x){
        int repr = x, y;
        // merg in sus pe arbore pana la radacina lui x
        while(repr != sets[repr])
            repr = sets[repr];
        // setez radacina lui x ca reprezentant pentru toti fiii
        while(x != sets[repr]){
            y = sets[x];
            sets[x] = repr;
            x = y;
        }
        return repr;
    }

    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        sets.clear();
        ranks.clear();
        sets.resize(n + 1);
        ranks.resize(n + 1);
        vector<bool> sol(queries.size());

        // retinem pozitia fiecarui query initial pentru ca in rezultat sa avem aceeasi ordine
        for(int i = 0; i < queries.size(); i++)
            queries[i].emplace_back(i);

        // sortam nodurile si queries dupa cost crescator
        sort(edgeList.begin(), edgeList.end(), comp);
        sort(queries.begin(), queries.end(), comp);

        for(auto el : queries){
            cout<<el[2]<<endl;
        }
        for(int i = 0; i < n; i++)
        {
            sets[i] = i;
            ranks[i] = 1;
        }
        int k = 0;
        // pentru fiecare query
        for(auto el: queries){
            // daca o muchie are costul mai mic decat costul cerut de query-ul actual unim reprezentantii muchilor respective
            // (inseamna ca pana la nodul actual fiecare muchie are costul mai mic decat cel din query)
            while (k < edgeList.size() && edgeList[k][2] < el[2]) {
                if(find(edgeList[k][0]) != find(edgeList[k][1]))
                    uni(find(edgeList[k][0]), find(edgeList[k][1]));
                k++;
            }
            // daca dupa union cele doua noduri au acelasi reprezentant inseamna ca am gasit un drum
            sol[el[3]] = (find(el[0])==find(el[1]));
        }
        return sol;
    }
};

int main(){
//    int n = 5;
//    vector<vector<int>> edgeList = {{0,1,10}, {1,2,5}, {2,3,9}, {3,4,13}};
//    vector<vector<int>> queris = {{0,4,14}, {1,4,13}};

//    int n = 3;
//    vector<vector<int>> edgeList = {{0,1,2}, {1,2,4}, {2,0,8}, {1,0,16}};
//    vector<vector<int>> queris = {{0,1,2}, {0,2,5}};

//    int n = 34;
//    vector<vector<int>> edgeList = {{17,26,57},{4,15,100},{31,18,23},{6,18,32},{12,26,19},{8,9,14},{18,33,99},{4,30,60},{27,5,52},{5,12,31},{30,16,63},{31,25,15},{32,5,89},{27,13,31},{11,5,30},{18,30,5},{10,31,21},{30,16,100},{1,5,15},{24,11,61},{2,10,97},{20,32,12},{24,17,1},{33,5,27},{11,6,71},{16,31,93},{16,32,59},{12,31,28},{22,13,79},{19,24,39},{28,17,36},{3,9,82},{19,10,88},{9,23,89},{17,2,70},{25,2,66},{30,8,74},{26,0,77},{25,23,86},{7,4,48},{22,11,21},{20,24,46},{30,20,41},{16,20,48},{28,0,77}};
//    vector<vector<int>> queries ={{14,25,32},{16,7,80},{16,2,2},{2,24,3},{17,4,30},{30,6,56},{0,4,89},{5,15,89},{10,18,40},{8,1,37},{19,2,13},{1,28,66},{7,16,24},{13,33,67},{32,31,26},{12,29,88},{8,24,72},{30,16,87},{6,26,14},{28,25,100},{12,13,54},{11,21,59},{26,8,60},{26,19,27},{20,26,80},{30,11,21},{15,7,49},{26,28,81},{4,32,22},{21,26,32},{22,25,46},{9,6,13},{21,26,9},{14,29,33},{5,3,13},{23,27,84},{7,6,27},{28,25,50},{2,10,78},{33,14,62},{12,19,76},{29,26,26},{6,8,9},{7,18,56},{26,17,91}};

    int n = 3;
    vector<vector<int>> edgeList = {{1, 2, 8}, {2,3,9}};
    vector<vector<int>> queries = {{1, 3, 10}};
    vector<bool> sol;
    sol = Solution().distanceLimitedPathsExist(n, edgeList, queries);
    for(auto && i : sol)
        if(i)
            cout<<"true, ";
        else
            cout<<"false, ";
    return 0;
}
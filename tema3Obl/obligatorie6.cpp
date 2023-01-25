#include <iostream>
#include <bits/stdc++.h>

using namespace std;
// compara fiecare litera cu fiecare litera din cele doua cuvinte
// retinem numarul de cuvinte comune pana la o anumita pozitie
// O(m * n) (dimensiunea primului * dimenisunea celui de-al doilea)
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int dimT1 = (int)text1.length();
        int dimT2 = (int)text2.length();

        // retinem numarul de litere comune pana la o anumita pozitie in cuvant
        vector<vector<int>> dim(dimT1 + 1, vector<int>(dimT2 + 1));
        for (int i = 0; i < text1.length(); i++)
            for (int j = 0; j < text2.length(); j++) {
                // daca gasim o litera comuna intre cele doua cuvinte
                // crestem numarul de litere pana la pozitia respectiva
                if (text1[i] == text2[j])
                    dim[i + 1][j + 1] = 1 + dim[i][j];
                // altfel alegem maximul dintre pozitiile anterioare
                else
                    dim[i + 1][j + 1] = max(dim[i][j + 1], dim[i + 1][j]);
            }
        return dim[dimT1][dimT2];
    }
};

int main() {
    Solution s;
    cout<<s.longestCommonSubsequence("abc", "abc");
    return 0;
}
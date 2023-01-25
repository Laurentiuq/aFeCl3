#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Lcs, retinem string-ul care e lcs intre str1 si str2
// din lcs construim un string adaugand caracterele din str1 si str2 care nu fac parte din lcs
// O(m * n) (len(str1) * len(str2))
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int pos1 = 0;
        int pos2 = 0;

        string sol = "";

        for(auto c : lcs(str1, str2)){
            // Adaugam caracterele care nu fac parte din lcs
            while(str1[pos1] != c) {
                sol += str1[pos1];
                pos1++;
            }
            while(str2[pos2] != c){
                sol += str2[pos2];
                pos2++;
            }
            // Adaugam caracterele din lcs
            sol += c;
            pos1++;
            pos2++;

        }
        // mai sus parcurgem lcs-ul, daca mai sunt caractere care nu sunt in lcs
        // adaugam toate caracterele care mai raman
        return sol + str1.substr(pos1) + str2.substr(pos2);
    }

    // algortimul de la problema anterioara doar ca retinem string

    string lcs(string& str1, string& str2){
        vector<vector<string>> lcsV(str1.length() + 1, vector<string>(str2.length() + 1));
        for(int i = 1; i <= str1.length(); i++)
            for(int j = 1; j <= str2.length(); j++) {
                // daca gasim un caracter comun il adaugam la caracterele comune
                // gasite pana la pozitia i
                if (str1[i - 1] == str2[j - 1])
                    lcsV[i][j] = lcsV[i - 1][j - 1] + str1[i - 1];
                // altfel alegem string-ul de dimensiune maxima gasit pana
                // la pozitiile anterioare(pentru str1 si pentru str2)
                else {
                    if (lcsV[i - 1][j].length() > lcsV[i][j - 1].length())
                        lcsV[i][j] = lcsV[i - 1][j];
                    else
                        lcsV[i][j] = lcsV[i][j - 1];
                }
            }
        return lcsV[str1.length()][str2.length()];
    }
};

int main(){

    return 0;
}
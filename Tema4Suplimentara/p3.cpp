#include <bits/stdc++.h>
using namespace std;
class Solution {
    vector<int> id;
    vector<int> sz;
    void un(int u, int v) {
        const int i = find(u);
        const int j = find(v);
        if (i == j)
            return;
        if (sz[i] < sz[j]) {
            sz[j] += sz[i];
            id[i] = j;
        } else {
            sz[i] += sz[j];
            id[j] = i;
        }
    }

    int find(int u) {
        return id[u] == u ? u : id[u] = find(id[u]);
    }
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<vector<string>> ans;
        unordered_map<string, int> emailToIndex;
        unordered_map<int, set<string>> indexToEmails;
        id.clear();
        sz.clear();

        id.resize(accounts.size(), 0);
        sz.resize(accounts.size(), 1);
        for(int i = 0; i < accounts.size(); i++)
            id[i] = i;
        for (int i = 0; i < accounts.size(); ++i) {
            const string name = accounts[i][0];
            for (int j = 1; j < accounts[i].size(); ++j) {
                const string email = accounts[i][j];
                const auto it = emailToIndex.find(email);
                if (it == emailToIndex.end()) {
                    emailToIndex[email] = i;
                } else {
                    un(i, it->second);
                }
            }
        }

        for (const auto& [email, index] : emailToIndex)
            indexToEmails[find(index)].insert(email);

        for (const auto& [index, emails] : indexToEmails) {
            const string name = accounts[index][0];
            vector<string> row{name};
            row.insert(end(row), begin(emails), end(emails));
            ans.push_back(row);
        }

        return ans;
    }
};

int main(){


    return 0;
}



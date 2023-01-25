#include <bits/stdc++.h>


using namespace std;
const int MAXN = 100001;

int N, K, numvis = 0;
string S[MAXN];
vector<string> substrings, ans;


vector<pair<int, int>> adj[MAXN << 1];
int check1[MAXN << 1], check2[MAXN << 1];
bool visited[MAXN];

void dfs(int node) {
    numvis++;
    while (!adj[node].empty()) {
        pair<int, int> new_node = adj[node].back();
        adj[node].pop_back();
        dfs(new_node.first);
    }
    string temp = "";
    temp += substrings[node][K - 2];
    ans.push_back(temp);
}

int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> S[i];
        substrings.push_back(S[i].substr(0, K - 1));
        substrings.push_back(S[i].substr(1));
    }
    if (K == 1) {
        for (int i = 1; i <= N; i++) {
            cout << S[i];
        }
        cout << '\n';
        return 0;
    }
    sort(substrings.begin(), substrings.end());
    substrings.resize(unique(substrings.begin(), substrings.end()) - substrings.begin());
    for (int i = 1; i <= N; i++) {
        int x = lower_bound(substrings.begin(), substrings.end(), S[i].substr(0, K - 1)) - substrings.begin();
        int y = lower_bound(substrings.begin(), substrings.end(), S[i].substr(1)) - substrings.begin();
        adj[x].emplace_back(y, i);
        check1[x]++;
        check2[y]++;
    }
    int cnt = 0, firs = 0;
    for (int i = 0; i < substrings.size(); i++) {
        cnt += (check1[i] != check2[i]);
        if (check1[i] > check2[i]) {
            firs = i;
        }
    }
    if (cnt > 2) {
        cout << -1 << '\n';
        return 0;
    }


    dfs(firs);
    ans.push_back(substrings[firs].substr(0, K - 2));
    if (numvis != N + 1) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
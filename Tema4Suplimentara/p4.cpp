#include <bits/stdc++.h>

using namespace std;


const int MAXN =  1010;

int n, mat[MAXN][MAXN], pairr[MAXN], pairl[MAXN], dist[MAXN], ans, t[MAXN][MAXN], pos[MAXN];
vector<int> gr[MAXN];


bool dfs(int v)
{
    if(v == 0)
        return 1;
    for(int i = 0; i < gr[v].size(); i++)
    {
        if(dist[pairr[gr[v][i]]] == dist[v] + 1)
        {
            if(dfs(pairr[gr[v][i]]) == 1)
            {
                pairl[v] = gr[v][i];
                pairr[gr[v][i]] = v;
                return 1;
            }
        }
    }
    return 0;
}

bool bfs()
{
    queue<int> q;
    for(int i = 1; i <= n; i++)
    {
        if(pairl[i] == 0)
        {
            dist[i] = 0;
            q.push(i);
        }
        else
            dist[i] = MAXN;
    }
    dist[0] = MAXN;
    int node;
    while(q.empty() == false)
    {
        node = q.front();
        q.pop();
        if(dist[node] < dist[0])
        {
            for(int i = 0; i < gr[node].size(); i++)
            {
                if(dist[pairr[gr[node][i]]] == MAXN)
                {
                    dist[pairr[gr[node][i]]] = dist[node] + 1;
                    q.push(pairr[gr[node][i]]);
                }

            }
        }
    }
    if(dist[0] != MAXN)
        return true;
    return false;
}

void calc_match()
{
    while(bfs() == 1)
    {
        for(int i = 1; i <= n; i++)
        {
            if(pairl[i] == 0)
            {
                if(dfs(i) == 1)
                    ans++;
            }
        }
    }
    return;
}

int main()
{
    cin>>n;

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            cin>>mat[i][j];
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(mat[i][j] == 1)
                gr[i].push_back(j);
        }
    }

    calc_match();

    for(int i = 1; i <= n; i++)
        pos[i] = i;
    if(ans != n)
    {
        cout<<"-1\n";
    }
    else
    {
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(pos[j] == pairl[i])
                {
                    cout<<"C "<< i<< " "<<j<<endl;
                    swap(pos[i], pos[j]);
                    break;
                }
            }
        }
    }


    return 0;
}
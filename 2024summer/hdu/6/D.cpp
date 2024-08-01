// 割边
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

const int maxN = 1e5+5;
int pa[maxN];
int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

// x 并 y 上
void merge(int x, int y) {
    pa[find(x)] = find(y);
}

int low[maxN], dfn[maxN], dfs_clock;
bool isbridge[maxN];
vector<int> edges[maxN];
int cnt_bridge;
int father[maxN];

void tarjan(int cur, int fa) {
    father[cur] = fa;
    low[cur] = dfn[cur] = ++dfs_clock;

    for (auto&& to : edges[cur]) {
        if (!dfn[to]) {
            tarjan(to, cur);
            low[cur] = min(low[cur], low[to]);
            
            if (low[to] > dfn[cur]) {
                isbridge[to] = true;
                ++cnt_bridge;
            }
        }
        else if (dfn[to] < dfn[cur] && to != fa) {
            low[cur] = min(low[cur], dfn[to]);
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<pii> qie, lun2;
    
    for (int i = 0; i < m; ++i) {
        int from, to;
        string s;
        cin >> from >> to >> s;
        if (s == "Lun") {
            edges[from].push_back(to);
            edges[to].push_back(from);

            lun2.push_back({from,to});
        }
        else {
            qie.push_back({from,to});
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (!father[i]) {
            dfs_clock = 0;
            tarjan(i,i);
        }
    }

    for (int i = 1; i <= n; ++i) {
        pa[i] = i;
    }
    vector<pii> ans;
    for (auto&& [u, v] : lun2) {
        if (isbridge[u] && father[u] == v)
            continue; 
        if (isbridge[v] && father[v] == u)
            continue; 
        
        ans.push_back({u,v});
    }
    
    vector<bool> vis2(n+1,false);
    auto dfs = [&](auto self, int x, int fa, int root) -> void {
        vis2[x] = true;
        for (auto&& to : edges[x]) {
            if (to == fa || (isbridge[to] && father[to] == x) || (isbridge[x] && father[x] == to) || vis2[to]) continue;
            merge(to,root);
            self(self, to, x, root);
        }
    };
    
    for (int i = 1; i <= n; ++i) {
        if (vis2[i]) continue;
        dfs(dfs,i,0,i);
    }

    
    for (auto&& [u, v] : qie) {
        if (find(u) != find(v)) {
            ans.push_back({u,v});
            merge(u,v);
        }
    }

    int rt = find(1);
    bool check = false;
    for (int i = 2; i <= n; ++i) {
        if (find(i) != rt) {
            check = true;
            break;
        }
    }

    if (check) {
        cout << "NO" << endl;
    }
    else {
        cout << "YES" << endl;
        cout << ans.size() << endl;
        for (auto&& [u, v] : ans) {
            cout << u << " " << v << endl;
        }
    }


    system("pause");
    return 0;
}

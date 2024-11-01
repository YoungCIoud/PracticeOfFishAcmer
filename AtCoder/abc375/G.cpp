#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e15;
constexpr int N = 2e5, M = 2e5;
// 找最短路径组成的图的割边
struct Edge {
    int u, v;
    i64 w;
};
std::vector<Edge> edge(M + 5);
std::vector<std::pair<int, i64>> g[N + 5];

void dij(int n, int S, std::vector<i64> &dis) {
    std::priority_queue<std::pair<i64, int>> q;
    q.push({ 0, S });
    std::vector<bool> vis(n + 1, false);
    dis[S] = 0;
    while (not q.empty()) {
        auto [d, cur] = q.top();
        q.pop();
        if (vis[cur]) {
            continue;
        }
        vis[cur] = true;
        d = -d;

        for (auto &[to, w] : g[cur]) {
            if (dis[to] >= d + w) {
                dis[to] = d + w;
                q.push({ -dis[to], to });
            }
        }
    }
    return;
}

int dfn[N + 5], low[N + 5], tim;
bool cut[M + 5];
void tragan(int cur, int fa, int n) {
    dfn[cur] = low[cur] = ++tim;
    int eid = 0;
    for (auto &[to, id] : g[cur]) {
        if (to == fa) {
            eid = id;
            continue;
        }

        if (dfn[to]) {
            low[cur] = std::min(low[cur], dfn[to]);
        }
        else {
            tragan(to, cur, n);
            low[cur] = std::min(low[cur], low[to]);
        }
    }

    if (low[cur] == dfn[cur] && eid != 0) {
        cut[eid] = true;
    }
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a = 0, b = 0;
        i64 c = 0;
        std::cin >> a >> b >> c;
        edge[i] = { a, b, c };
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }

    std::vector d1(n + 1, Inf), dn(n + 1, Inf);
    dij(n, 1, d1), dij(n, n, dn);
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        auto &[u, v, w] = edge[i];
        if (d1[u] + w + dn[v] == d1[n] || d1[v] + w + dn[u] == d1[n]) {
            // printf("%d - %d\n", u, v);
            g[u].push_back({ v, i });
            g[v].push_back({ u, i });
        }
    }
    tragan(1, 0, n);

    for (int i = 1; i <= m; i++) {
        std::cout << (cut[i] ? "Yes\n" : "No\n");
    }
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
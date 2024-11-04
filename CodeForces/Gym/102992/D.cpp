#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 2e5, Inf = 1e9;
std::vector<int> fa(N + 5, 0), g[N + 5];

int getfa(int u) {
    return fa[u] == u ? u : (fa[u] = getfa(fa[u]));
}

void dfs(int cur, int lst, int fst) {
    fa[cur] = fst;
    for (auto &to : g[cur]) {
        if (to != lst) {
            dfs(to, cur, fst);
        }
    }
    return;
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        g[i].clear();
    }

    std::vector<std::array<int, 2>> edge;
    while (m--) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        if (u == v) {
            continue;
        }
        if (u > v) {
            std::swap(u, v);
        }

        edge.push_back({ u, v });
    }
    std::sort(edge.begin(), edge.end());
    edge.erase(unique(edge.begin(), edge.end()), edge.end());
    m = edge.size();
    std::map<std::pair<int, int>, int> pos;
    std::vector deg(n + 1, 0);
    std::vector used(m, false);
    for (int i = 0; i < m; i++) {
        auto &[u, v] = edge[i];
        pos[{ u, v }] = pos[{ v, u }] = i;
        int fu = getfa(u), fv = getfa(v);
        if (fu != fv) {
            g[u].push_back(v);
            g[v].push_back(u);
            deg[u]++, deg[v]++;
            fa[fu] = fv;
            used[i] = true;
        }
    }

    int rt = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] * 2 > n) {
            rt = i;
            break;
        }
    }
    if (rt != 0) {
        fa[rt] = rt;
        for (auto &to : g[rt]) {
            dfs(to, rt, to);
        }

        for (int i = 0; i < m && deg[rt] * 2 > n; i++) {
            if (used[i]) {
                continue;
            }

            auto &[u, v] = edge[i];
            int fu = getfa(u), fv = getfa(v);
            if (fu == fv || u == rt || v == rt) {
                continue;
            }

            bool ok = false;
            deg[u]++, deg[v]++;
            if (not ok) { // 尝试删除 rt - fu
                deg[fu]--;
                if (deg[fu] * 2 <= n && deg[fv] * 2 <= n) {
                    used[pos[{ fu, rt }]] = false;
                    ok = true;
                    fa[fu] = fv;
                }
                else {
                    deg[fu]++;
                }
            }
            if (not ok) { // 尝试删除 rt - fv
                deg[fv]--;
                if (deg[fu] * 2 <= n && deg[fv] * 2 <= n) {
                    used[pos[{ fv, rt }]] = false;
                    ok = true;
                    fa[fv] = fu;
                }
                else {
                    deg[fv]++;
                }
            }

            if (ok) {
                deg[rt]--;
                used[i] = true;
            }
            else {
                deg[u]--, deg[v]--;
            }
        }
    }

    if (deg[rt] * 2 <= n) {
        std::cout << "Yes\n";
        for (int i = 0; i < m; i++) {
            if (used[i]) {
                std::cout << edge[i][0] << ' ' << edge[i][1] << '\n';
            }
        }
    }
    else {
        std::cout << "No\n";
    }
    return;
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}

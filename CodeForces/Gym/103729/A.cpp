#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 300;
i64 g[N + 5][N + 5];
int sp[N + 5];
int fa[N + 5];
bool issp[N + 5];

int find(int u) {
    return u == fa[u] ? u : (fa[u] = find(fa[u]));
}
bool merge(int u, int v) {
    int fu = find(u), fv = find(v);
    fa[fv] = fu;
    return fu != fv;
}

struct Edge {
    int u, v;
    i64 val;
};

void solve()
{
    int n = 0, m = 0, q = 0, t = 0;
    std::cin >> n >> m >> q >> t;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            g[i][j] = (i == j) ? 0ll : Inf;
        }
    }
    int cnt = 0;
    std::iota(fa + 1, fa + 1 + n, 1);
    for (int i = 0; i < m; i++) {
        int x = 0, y = 0, c = 0;
        std::cin >> x >> y >> c;
        merge(x, y);
        g[x][y] = g[y][x] = std::min(g[x][y], 1ll * c);
    }
    for (int i = 1; i <= n; i++) {
        if (fa[i] == i) {
            cnt++;
        }
    }
    if (cnt != 1) {
        std::cout << "-1\n";
        return;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    for (int i = 0; i < q; i++) {
        std::cin >> sp[i];
        issp[sp[i]] = true;
    }
    
    std::vector<Edge> e;
    for (int i = 0; i < q; i++) {
        for (int j = i + 1; j < q; j++) {
            e.push_back({ sp[i], sp[j], g[sp[i]][sp[j]] });
        }
    }
    std::sort(e.begin(), e.end(), [] (auto &u, auto &v) -> bool { return u.val < v.val; });
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    i64 mn1 = 0;
    for (auto &[u, v, val] : e) {
        if (merge(u, v)) {
            mn1 = val;
        }
    }

    i64 mn2 = 0;
    for (int i = 1; i <= n; i++) {
        if (not issp[i]) {
            i64 mn3 = Inf;
            for (int j = 0; j < q; j++) {
                mn3 = std::min(mn3, g[i][sp[j]]);
            }
            mn2 = std::max(mn2, mn3);
        }
    }

    i64 mx = std::max(mn1, mn2 * 2ll);
    std::cout << ((t == 0) ? -1 : (mx + t - 1) / t) << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    system("pause");

    return 0;
}

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
constexpr int N = 500 * 500, M = 1e6, Inf = 1e9, L = 20;

int fa[N];
int get(int u) {
    return u == fa[u] ? u : (fa[u] = get(fa[u]));
}
bool merge(int u, int v) {
    int fu = get(u), fv = get(v);
    fa[fv] = fu;
    return fu != fv;
}

std::vector<std::array<int, 2>> g[N];
std::vector st(N, std::vector(L, std::array<int, 2>{})); 
std::vector deep(N, 0);
void dfs(int cur) {
    for (int l = 1; (1 << l) <= deep[cur]; l++) {
        st[cur][l][0] = st[st[cur][l - 1][0]][l - 1][0];
        st[cur][l][1] = std::min(st[cur][l - 1][1], st[st[cur][l - 1][0]][l - 1][1]);
    }

    for (auto &[to, val] : g[cur]) {
        if (to == st[cur][0][0]) {
            continue;
        }

        st[to][0] = { cur, val };
        deep[to] = deep[cur] + 1;
        dfs(to);
    }
}

int LCA(int u, int v) {
    if (deep[u] != deep[v]) {
        if (deep[u] > deep[v]) {
            std::swap(u, v);
        }
        for (int i = L; i >= 0; i--) {
            if (deep[v] - (1 << i) >= deep[u]) {
                v = st[v][i][0];
            }
        }
    }

    if (u == v) {
        return u;
    }

    for (int i = L; i >= 0; i--) {
        if ((1 << i) <= deep[u] && st[u][i][0] != st[v][i][0]) {
            u = st[u][i][0];
            v = st[v][i][0];
        }
    }
    return st[u][0][0];
}

int minval(int u, int v) {
    if (deep[u] > deep[v]) {
        std::swap(u, v);
    }
    int res = Inf;
    for (int d = deep[v] -  deep[u], l = 0; d; d >>= 1, l++) {
        if (d & 1) {
            res = std::min(res, st[v][l][1]);
            v = st[v][l][0];
        }
    }
    return res;
}

void solve()
{
    int h = 0, w = 0;
    std::cin >> h >> w;
    std::vector f(h, std::vector(w, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            std::cin >> f[i][j];
        }
    }

    // 分离边
    std::vector<std::array<int, 3>> edge;
    for (int i = 0; i < h; i++) {
        for (int j = 1; j < w; j++) {
            int u = i * w + j;
            edge.push_back({ u - 1, u, std::min( f[i][j], f[i][j - 1]) });
        }
    }
    for (int j = 0; j < w; j++) {
        for (int i = 1; i < h; i++) {
            int u = i * w + j;
            edge.push_back({ u - w, u, std::min( f[i][j], f[i - 1][j]) });
        }
    }

    // 生成树的边
    std::sort(edge.begin(), edge.end(), [](auto &u, auto &v) {
        return u[2] > v[2];
    });
    for (int i = 0; i < h * w; i++) {
        fa[i] = i;
    }
    for (auto &[u, v, val] : edge) {
        if (merge(u, v)) {
            g[u].push_back({ v, val });
            g[v].push_back({ u, val });
        }
    }

    // 生成树上维护 lca 和 st 表
    dfs(0);

    int q = 0;
    std::cin >> q;
    while (q--) {
        int a = 0, b = 0, x = 0;
        int c = 0, d = 0, z = 0;
        std::cin >> a >> b >> x >> c >> d >> z;
        a--, b--, c--, d--;

        int u = a * w + b, v = c * w + d;
        
        int lca = LCA(u, v);
        
        std::cout << x + z - 2 * std::min({ x, z, minval(u, lca), minval(v, lca) }) << '\n';
    }
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

    sp();

    return 0;
}
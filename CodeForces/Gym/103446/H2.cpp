#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;
typedef std::array<int, 3> edge;
int val[N * 2 + 5], len[2 * N + 5];
std::vector<int> g[N * 2 + 5];

int fa[N * 2 + 5];
int getfa(int u) {
    return fa[u] == u ? u : (fa[u] = getfa(fa[u]));
}

std::array<int, 2> st[N * 2 + 5][25];
int dfs(int cur) {
    for (auto &to : g[cur]) {
        val[cur] += dfs(to);
        st[to][0] = { cur, len[cur] };
    }
    return val[cur];
}

void solve()
{
    int n = 0, m = 0, q = 0;
    std::cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> val[i];
    }
    std::vector e(m, edge{});
    for (auto &[u, v, w] : e) {
        std::cin >> u >> v >> w;
    }
    std::sort(e.begin(), e.end(), [](edge u, edge v){
        return u[2] < v[2];
    });

    // kruskal 重构树
    for (int i = 1; i <= n * 2; i++) {
        fa[i] = i;
    }
    int cnt = 0;
    for (auto &[u, v, w] : e) {
        int fu = getfa(u);
        int fv = getfa(v);
        if (fu == fv) {
            continue;
        }

        cnt++;
        g[n + cnt].push_back(fu);
        g[n + cnt].push_back(fv);
        fa[fv] = fa[fu] = n + cnt;
        len[n + cnt] = w;
    }
    dfs(cnt + n);
    for (int i = 1; i < n + cnt; i++) {
        st[i][0][1] -= val[i];
    }
    for (int l = 1; l < 25; l++) {
        for (int i = 1; i + (1 << l) <= n + cnt; i++) {
            st[i][l][0] = st[st[i][l - 1][0]][l - 1][0];
            st[i][l][1] = std::max(st[i][l - 1][1], st[st[i][l - 1][0]][l - 1][1]);
        }
    }

    while (q--) {
        int x = 0, k = 0;
        std::cin >> x >> k;
        for (int l = 24; l >= 0; l--) {
            if (st[x][l][0] != 0 && k >= st[x][l][1]) {
                x = st[x][l][0];
            }
        }
        std::cout << val[x] + k << '\n';
    }
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;
int fa[N];


int getfa(int u) {
    return fa[u] == u ? u : (fa[u] = getfa(fa[u]));
}

typedef std::array<int, 3> edge;
void solve()
{
    int n = 0, m = 0, q = 0;
    std::cin >> n >> m >> q;
    std::vector val(n, 0), ans(q, 0);
    for (auto &i : val) {
        std::cin >> i;
    }
    std::vector e(m, edge{});
    for (auto &[u, v, w] : e) {
        std::cin >> u >> v >> w;
        u--, v--;
    }
    std::sort(e.begin(), e.end(), [](edge u, edge v){
        return u[2] < v[2];
    });
    // 关于第x个点的询问, 记录初始值和id
    std::vector qr(n, std::multiset<std::array<int, 2>>{});
    for (int i = 0; i < q; i++) {
        int x = 0, k = 0;
        std::cin >> x >> k;
        qr[x - 1].insert({ k, i });
    }
    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }

    for (auto [u, v, w] : e) {
        u = getfa(u);
        v = getfa(v);
        if (u == v) {
            continue;
        }
        while (not qr[u].empty() && (*qr[u].begin())[0] + val[u] < w) {
            auto &[k, id] = *qr[u].begin();
            ans[id] = val[u] + k;
            qr[u].erase(qr[u].begin());
        } 
        while (not qr[v].empty() && (*qr[v].begin())[0] + val[v] < w) {
            auto &[k, id] = *qr[v].begin();
            ans[id] = val[v] + k;
            qr[v].erase(qr[v].begin());
        }

        if (qr[u].size() > qr[v].size()) {
            std::swap(u, v);
        }
        // 把u合并到v上
        while (not qr[u].empty()) {
            qr[v].insert(*qr[u].begin());
            qr[u].erase(qr[u].begin());
        }
        val[v] += val[u];
        fa[u] = v;
    }
    for (int i = 0; i < n; i++) {
        if (fa[i] == i) {
            for (auto &[k, id] : qr[i]) {
                ans[id] = k + val[i];
            }
        }
    }

    for (auto &i : ans) {
        std::cout << i << '\n';
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
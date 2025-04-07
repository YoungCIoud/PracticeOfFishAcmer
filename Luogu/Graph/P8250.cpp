#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), \
                std::cin.tie(0), \
                std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, M = 7e5, Inf = 1e9;

std::vector<int> g[N + 5];
std::vector<std::pair<int, int>> qr[N + 5];
bool vis[N + 5];
int ans[N + 5];

void solve()
{
    int n = 0, m = 0, q = 0;
    std::cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < q; i++) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        qr[l].push_back({ r, i });
    }
    for (int i = 1; i <= n; i++) {
        if (not qr[i].empty()) {
            std::sort(qr[i].begin(), qr[i].end());
        }
    }
    for (int l = 1; l <= n; l++) {
        if (qr[l].empty()) {
            continue;
        }
        std::fill(vis + 1, vis + 1 + n, false);
        for (int i = 0; i < g[l].size(); i++) {
            vis[g[l][i]] = true;
        }

        for (int i = 0, lstr = 0, lstans = 0; i < qr[l].size(); i++) {
            auto &[r, idx] = qr[l][i];
            if (r == lstr) {
                ans[idx] = lstans;
                continue;
            }
            else {
                ans[idx] = g[l].size();
                ans[idx] -= vis[r];
                for (auto &to: g[r]) {
                    ans[idx] -= vis[to];
                }
                lstr = r, lstans = ans[idx];
            }
        }
    }
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << '\n';
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
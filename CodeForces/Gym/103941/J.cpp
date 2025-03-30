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
constexpr int N = 1e6, Inf = 1e9;

int n = 0, rt = 0;
int v[N + 5], siz[N + 5], mn[N + 5], ans[N + 5];
std::vector<int> g[N + 5];

void dfs(int cur, int fa) {
    siz[cur] = 1;
    mn[cur] = v[cur];
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        dfs(to, cur);
        siz[cur] += siz[to];
        mn[cur] = std::min(mn[cur], mn[to]);
    }

    if (mn[cur] == v[cur]) {
        ans[v[cur]] = n - siz[cur];
    }
}

void solve()
{
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> v[i];
        if (v[i] == 0) {
            rt = i;
        }
    }
    for (int i = 2; i <= n; i++) {
        int u = 0;
        std::cin >> u;
        g[u].push_back(i);
        g[i].push_back(u);
    }

    dfs(rt, 0);
    int mx = 0;
    for (auto &to : g[rt]) {
        mx = std::max(mx, siz[to]);
    }
    std::cout << mx << ' ';
    for (int i = 1; i < n; i++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << n << '\n';
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

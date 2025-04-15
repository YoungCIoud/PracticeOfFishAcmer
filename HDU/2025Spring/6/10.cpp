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
constexpr int N = 2e5, M = 1e5, Inf = 1e9;
std::vector<int> g[N + 5];
i64 n = 0;
i64 siz[N + 5];
i64 ans[N + 5];

void dfs(int cur, int fa) {
    siz[cur] = 1;
    
    i64 cnt = (n - 1) * (n - 1);
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }
        
        dfs(to, cur);
        siz[cur] += siz[to];
        cnt -= siz[to] * siz[to];
    }
    
    cnt -= (n - siz[cur]) * (n - siz[cur]);
    cnt >>= 1;
    ans[cur] = n + cnt;
    ans[cur] += (n - siz[cur]) * (siz[cur] + (cnt - (n - siz[cur]) * (siz[cur] - 1)));
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }
        
        ans[cur] += siz[to] * ((n - siz[to]) + (cnt - siz[to] * (n - siz[to] - 1)));
    }
    return;
}

void solve()
{
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    // sp();

    return 0;
}
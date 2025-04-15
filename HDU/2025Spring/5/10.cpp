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
constexpr int N = 5e5, Inf = 1e9;

std::vector<std::array<int, 2>> g[N + 5];
std::array<int, 2> cnt;

void dfs(int cur, int fa, int d) {
    cnt[d]++;
    for (auto &[to, val] : g[cur]) {
        if (to != fa) {
            dfs(to, cur, d ^ val);
        }
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;
    
    cnt[0] = cnt[1] = 0;
    for (int i = 1; i <= n; i++)  {
        g[i].clear();
    }

    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0, w = 0;
        std::cin >> u >> v >> w;
        w %= 2;
        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
    }

    dfs(1, 0, 0);
    std::cout << 1ll * cnt[0] * cnt[0] * cnt[0] + 1ll * cnt[1] * cnt[1] * cnt[1] << '\n';
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

    sp();

    return 0;
}
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
constexpr int N = 3e5, M = 1e5, Inf = 1e9;

std::vector<int> g[N + 5], depth(N + 5);

void dfs(int cur, int dep) {
    depth[cur] = dep;
    for (auto &to : g[cur]) {
        dfs(to, dep + 1);
    }
    return;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }

    for (int i = 2; i <= n; i++) {
        int p = 0;
        std::cin >> p;
        g[p].push_back(i);
    }

    dfs(1, 0);
    int mx = *std::max_element(depth.begin() + 1, depth.begin() + 1 + n);
    std::vector lay(mx + 1, std::vector<int>{});
    std::vector ans(mx + 1, 0ll), f(n + 1, 0ll);
    for (int i = 2; i <= n; i++) {
        lay[depth[i]].push_back(i);
    }
    ans[mx] = lay[mx].size();
    for (auto &cur : lay[mx]) {
        f[cur] = 1;
    }

    for (int i = mx - 1; i >= 1; i--) {
        for (auto &cur : lay[i]) {
            i64 sum = 0;
            for (auto &to : g[cur]) {
                (sum += f[to]) %= Mod;
            }
            f[cur] = (1 + ans[i + 1] - sum + Mod) % Mod;
            (ans[i] += f[cur]) %= Mod;
        }
    }

    std::cout << (1 + ans[1]) % Mod << '\n';
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
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

constexpr i64 Mod = 998244353, Inf = 1e15;
constexpr int N = 100, M = 1e5;
int n;
i64 sum;
std::vector<int> g[N + 5], w(N + 5), siz(N + 5);
std::vector ans(N + 5, 0ll);

void dfs(int cur, int fa, int len) {
    siz[cur] = w[cur];
    ans[1] += 1ll * w[cur] * len;
    for (auto &to : g[cur]) {
        if (to != fa) {
            dfs(to, cur, len + 1);
            siz[cur] += siz[to];
        }
    }
}

void dfs(int cur, int fa) {
    for (auto &to : g[cur]) {
        if (to != fa) {
            ans[to] = ans[cur] + (sum - siz[to] - siz[to]);
            dfs(to, cur);
        }
    }
}

void solve()
{
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> w[i];
        sum += w[i];
        int u = 0, v = 0;
        std::cin >> u >> v;
        if (u != 0) {
            g[i].push_back(u);
            g[u].push_back(i);
        }
        if (v != 0) {
            g[i].push_back(v);
            g[v].push_back(i);
        }
    }
    dfs(1, 0, 0);
    dfs(1, 0);

    i64 res = Inf;
    for (int i = 1; i <= n; i++) {
        res = std::min(res, ans[i]);
    }
    std::cout << res << '\n';
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
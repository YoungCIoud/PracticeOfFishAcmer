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
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector g(2 * n + 1, std::vector<std::pair<int, i64>>{});
    for (int i = 0; i < m; i++) {
        int u = 0, v = 0, w = 0;
        std::cin >> u >> v >> w;
        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
        g[u].push_back({ v + n, 0 });
        g[v].push_back({ u + n, 0 });
        g[u].push_back({ u + n, 0 });
        g[v].push_back({ v + n, 0 });
        g[u + n].push_back({ v + n, w });
        g[v + n].push_back({ u + n, w });
    }

    for (int i = 1; i <= n; i++) {
        i64 a = 0;
        std::cin >> a;
        g[0].push_back({ i, a });
    }

    std::vector ans(2 * n + 1, Inf);
    ans[0] = 0;
    std::priority_queue<std::pair<i64, int>> q;
    q.push({ 0, 0 });
    std::vector vis(2 * n + 1, false);
    while (!q.empty()) {
        auto [d, cur] = q.top();
        q.pop();
        if (vis[cur]) {
            continue;
        }
        vis[cur] = true;
        d = -d;

        for (auto [to, w] : g[cur]) {
            if (ans[to] > d + w) {
                ans[to] = d + w;
                q.push({ -ans[to], to });
            }
        }
    }

    std::cout << (*std::max_element(ans.begin() + 1 + n, ans.end())) << '\n';
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

    sp();

    return 0;
}
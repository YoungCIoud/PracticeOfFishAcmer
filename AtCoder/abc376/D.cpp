#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, M = 2e5, Inf = 1e9;

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n + 1);
    for (int i = 1; i <= m; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);

        if (v == 1) {
            g[u].push_back(0);
        }
    }

    std::vector dis(n + 1, Inf);
    std::priority_queue<std::pair<int, int>> q;
    q.push({ 0, 1 });
    std::vector vis(n + 1, false);
    while (!q.empty()) {
        auto [d, cur] = q.top();
        q.pop();
        
        if (vis[cur]) {
            continue;
        }
        vis[cur] = true;
        d = -d;
        dis[cur] = d;
        
        for (auto &to : g[cur]) {
            if (dis[to] > d + 1) {
                q.push({ - d - 1, to });
            }
        }
    }

    std::cout << (dis[0] == Inf ? -1 : dis[0]) << '\n';

    return;
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector g(n + 1, std::vector<int>{});
    for (int i = 1; i < n; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector vis(n + 1, false);
    std::queue<std::array<int, 2>> q;
    q.push({ 1, 1 });
    vis[1] = true;
    std::vector fa(n + 1, 0), suf(n + 2, 0), out(n + 1, 0);
    std::vector<std::array<int, 2>> leaves;
    while (not q.empty()) {
        auto [cur, dep] = q.front();
        suf[dep]++;
        q.pop();

        bool is_leaf = true;
        for (auto &to : g[cur]) {
            if (not vis[to]) {
                is_leaf = false;
                vis[to] = true;
                q.push({ to, dep + 1});
                fa[to] = cur;
                out[cur]++;
            }
        }

        if (is_leaf) {
            leaves.push_back({ cur, dep });
        }
    }
    for (int i = n; i >= 1; i--) {
        suf[i] += suf[i + 1];
    }

    std::vector pre(n + 1, 0);
    for (auto [cur, dep] : leaves) {
        while (cur != 1 && out[cur] <= 1) {
            pre[dep]++;
            cur = fa[cur];
        }
        out[cur]--;
    }
    for (int i = 1; i <= n; i++) {
        pre[i] += pre[i - 1];
    }

    int ans = n;
    for (int i = 1; i <= n; i++) {
        ans = std::min(ans, suf[i + 1] + pre[i - 1]);
    }
    std::cout << ans << '\n';
}

int main()
{
    // IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
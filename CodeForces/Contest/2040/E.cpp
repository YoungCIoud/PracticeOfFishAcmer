#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 998244353;
constexpr int N = 2e3;

int n;
std::vector<int> g[N + 5], d(N + 5);
std::vector dp(N + 5, std::vector(N + 5, std::array<int, 2>{}));

void dfs(int cur, int fa) {
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        for (int p = 0; p <= n; p++) {
            dp[to][p][1] = (dp[cur][p][0] + 1) % Mod;
            dp[to][p][0] = dp[cur][p][1] + 2 * d[to] - 1;
            if (p > 0) {
                dp[to][p][0] = std::min(dp[to][p][0], dp[cur][p - 1][1] + 1);
            }
            dp[to][p][0] %= Mod;
        }
        dfs(to, cur);
    }
}

void solve() {
    int q = 0;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        d[i] = 0;
    }
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        d[u]++, d[v]++;
    }

    dfs(1, 0);
    while (q--) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        std::cout << dp[u][v][1] << '\n';
    }
    return;
}

int main () {
    int _t = 1;
    std::cin >> _t;
    while (_t--) {
        solve();
    }
    return 0;
}
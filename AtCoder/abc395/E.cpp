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
constexpr int N = 2e5, M = 2e5;

std::vector<int> g1[N + 5], g2[N + 5];

void solve()
{
    int n = 0, m = 0;
    i64 x = 0;
    std::cin >> n >> m >> x;
    for (int i = 0; i < m; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g1[u].push_back(v);
        g2[v].push_back(u);
    }

    std::priority_queue<std::pair<i64, int>> q;
    std::vector dis(2 * n + 1, Inf);
    std::vector vis(2 * n + 1, false);
    dis[n + 1] = 0;
    q.push({ 0, 1 });

    auto upd = [&](int cur, i64 d, bool inv) -> void {
        for (auto to : (inv ? g2[cur] : g1[cur])) {
            if (inv) {
                to = -to;
            }
            if (not vis[n + to] && d + 1 < dis[n + to]) {
                dis[n + to] = d + 1;
                q.push({ -dis[n + to], to });
            }
        }
    };
    while (not q.empty()) {
        auto [d, cur] = q.top();
        q.pop();
        if (vis[n + cur]) {
            continue;
        }
        vis[n + cur] = true;

        bool inv = (cur < 0);
        upd(std::abs(cur), -d, cur < 0);
        if (x - d < dis[n - cur]) {
            dis[n - cur] = x - d;
            q.push({ d - x, -cur });
        }
    }
    std::cout << std::min(dis[0], dis[n + n]) << '\n';
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
#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    #define cout cout << ">>>\t"
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, M = 1e5, Inf = 1e9;
std::vector<int> g[N + 5];

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    i64 ans = 0;
    std::vector<bool> vis(n + 1, false);
    std::queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (g[i].size() != 3 || vis[i]) {
            continue;
        }

        q.push(i);
        vis[i] = true;
        i64 cnt = 0;
        while (not q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto &to : g[cur]) {
                if (vis[to]) {
                    continue;
                }
                if (g[to].size() == 2) {
                    cnt++;
                }
                if (g[to].size() == 3) {
                    q.push(to);
                    vis[to] = true;
                }
            }
        }
        ans += cnt * (cnt - 1) / 2ll;
    }
    std::cout << ans << '\n';
    return;
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
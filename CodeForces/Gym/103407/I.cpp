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
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

using Node = std::pair<int, int>;

void solve()
{
    int h = 0, n = 0;
    std::cin >> h >> n;
    std::vector a(n, std::pair<Node, bool>{});
    for (auto &[p, block] : a) {
        std::cin >> p.first >> p.second;
        block = true;
    }
    
    int m = 0;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        Node p;
        std::cin >> p.first >> p.second;
        a.push_back({ p, false });
    }

    std::sort(a.begin(), a.end());
    std::unordered_map<int, int> dp;
    dp[0] = 0;
    for (auto &[p, block] : a) {
        auto &[x, y] = p;
        int sla = (x + y) % (2 * h), bas = (x - y) % (2 * h);
        if (block) {
            if (dp.count(sla) || dp.count(bas))
                dp[sla] = dp[bas] = std::max(dp[sla], dp[bas]);
        }
        else {
            if (dp.count(sla)) dp[sla]++;
            if (dp.count(bas)) dp[bas]++;
        }
    }

    // std::cout << dp[0] << '\n';
    int ans = 0;
    for (auto &[k, num] : dp) {
        ans = std::max(ans, num);
    }
    std::cout << ans << '\n';
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
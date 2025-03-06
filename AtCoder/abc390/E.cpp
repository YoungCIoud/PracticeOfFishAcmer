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
constexpr int N = 5e3, M = 2e5, Inf = 1e9;

void solve()
{
    int n = 0, x = 0;
    std::cin >> n >> x;
    std::vector val(3, std::vector<std::pair<int, int>>{});
    for (int i = 0; i < n; ++i)
    {
        int a = 0, b = 0, c = 0;
        std::cin >> a >> b >> c;
        val[a - 1].emplace_back(b, c);
    }

    auto work = [&](std::vector<std::pair<int, int>> &v) -> std::vector<int> {
        std::vector dp(x + 1, 0); // dp[i] 表示花费 i 的最大价值
        for (int i = 0; i < v.size(); ++i)
        {
            for (int j = x; j >= v[i].second; --j)
            {
                dp[j] = std::max(dp[j], dp[j - v[i].second] + v[i].first);
            }
        }
        return dp;
    };

    std::vector dp = { work(val[0]), work(val[1]), work(val[2]) };
    std::array<int, 3> id{0, 0, 0};
    for (int i = 0; i < x; ++i)
    {
        int mn = std::min({ dp[0][id[0]], dp[1][id[1]], dp[2][id[2]] });
        for (int j = 0; j < 3; ++j)
        {
            if (dp[j][id[j]] == mn)
            {
                ++id[j];
                break;
            }
        }
    }

    std::cout << std::min({ dp[0][id[0]], dp[1][id[1]], dp[2][id[2]] }) << '\n';
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
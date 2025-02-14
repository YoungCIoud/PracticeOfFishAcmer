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

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0, c1 = 0, c2 = 0;
    std::cin >> n >> c1 >> c2;
    std::vector a(n + 1, 0ll), b(n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i] >> b[i];
    }
    a.push_back(Inf), b.push_back(Inf);
    // dp[i][0/1] 前 i 条记录不变第 i 条 / 反转第 i 条 所需要的最小代价
    std::vector dp(n + 2, std::vector(2, Inf));
    dp[0] = { 0, 0 };
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] <= a[i] && b[j] <= b[i]) {
                dp[i][0] = std::min(dp[i][0], dp[j][0] + 1ll * (i - j - 1) * c1);
                dp[i][1] = std::min(dp[i][1], dp[j][1] + 1ll * (i - j - 1) * c1 + c2);
            }
            if (a[j] <= b[i] && b[j] <= a[i]) {
                dp[i][1] = std::min(dp[i][1], dp[j][0] + 1ll * (i - j - 1) * c1 + c2);
                dp[i][0] = std::min(dp[i][0], dp[j][1] + 1ll * (i - j - 1) * c1);
            }
        }
    }
    std::cout << dp[n + 1][0] << '\n';
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
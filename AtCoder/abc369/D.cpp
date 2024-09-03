#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    vct a(n + 1, 0ll);
    for (int i = 1; i <= n; i++) std::cin >> a[i];

    // dp[i][0]: 打到第i只怪且第i只怪是第偶数只
    // dp[i][0]: 打到第i只怪且第i只怪是第奇数只
    vct dp(n + 1, vct<i64>(2, 0));
    dp[0][0] = 0, dp[0][1] = -Inf;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i - 1; j >= std::max(0, i - 2); j--)
        {
            dp[i][1] = std::max(dp[i][1], dp[j][0] + a[i]);
            dp[i][0] = std::max(dp[i][0], dp[j][1] + a[i] + a[i]);
        }
    }
    
    std::cout << std::max({dp[n][0], dp[n][1], dp[n - 1][0], dp[n - 1][1]}) << '\n';
    return;
}

int main()
{
    //IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
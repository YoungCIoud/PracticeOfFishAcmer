#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 2e5, M = 1e9;

void solve()
{
    int n = 0;
    i64 k = 0;
    std::cin >> n >> k;
    vct<i64> pre(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> pre[i];
        pre[i] += pre[i - 1];
    }

    vct<int> dp(n + 1, 0);
    int sum = 1;
    std::unordered_map<i64, int> cnt;
    cnt[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = (sum - cnt[pre[i] - k] + Mod) % Mod;
        sum = (sum + dp[i]) % Mod;
        cnt[pre[i]] = (cnt[pre[i]] + dp[i]) % Mod;
    }
    std::cout << dp[n] << '\n';
    // vct<i64> dp(n + 1, 0);
    // dp[0] = 1;
    // for (int i = 1; i <= n; i++)
    //     for (int j = 1; j <= i; j++)
    //         if (pre[i] - pre[j - 1] != k)
    //             dp[i] += dp[j - 1];
    // std::cout << dp[n] << '\n';
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
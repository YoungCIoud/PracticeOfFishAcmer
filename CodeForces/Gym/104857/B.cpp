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
constexpr int N = 500, M = 500, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n + 1);
    int m = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        m += a[i];
    }
    std::vector C(m + 1, std::vector(m + 1, 0ll));
    C[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod;
        }
    }

    // dp[i][j]: 序列由前i个数组成且最早出现LIS = 2的地方在第j个位置
    std::vector dp(n + 5, std::vector(m + 5, 0ll));
    dp[0][1] = 1;
    for (int i = 1, pre = 0; i <= n; pre += a[i], i++) {
        for (int j = 1; j <= pre + 1; j++) {
            if (dp[i - 1][j] == 0) {
                continue;
            }

            // 枚举在 1 的后面，出现的第一个 i
            for (int k = 1; k < j; k++) {
                // 枚举 1 前面的 i
                for (int x = 0; x < a[i]; x++) {
                    (dp[i][x + k + 1] += dp[i - 1][j] * C[j - k - 1 + a[i] - x - 1][a[i] - x - 1]) %= Mod;
                }
            }
            // x = a[i]
            (dp[i][j + a[i]] += dp[i - 1][j]) %= Mod;
        }
    }
    i64 ans = 0;
    for (int i = 1; i <= m + 1; i++) {
        (ans += dp[n][i]) %= Mod;
    }
    std::cout << ans << '\n';
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
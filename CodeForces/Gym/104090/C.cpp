#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 3e3, M = 1e5, P = 10, Inf = 0x3f3f3f3f;

// 分支三最多会被选择一次
void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector a(n + 1, std::vector(P + 1, 0));
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i][0];
        sum += a[i][0];
        for (int j = 1; j <= a[i][0]; j++) {
            std::cin >> a[i][j];
        }
    }

    // dp[i][j][0/1] 前i个物品, 总能量是j, 且是否有物品进入过分支三
    std::vector dp(n + 1, std::vector(k + 1, std::array<int, 2>{}));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = { -Inf, -Inf };
        }
    }
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            // 分支1
            if (j >= a[i][0]) {
                dp[i][j] = dp[i - 1][j - a[i][0]];
                dp[i][j][0] += a[i][a[i][0]];
                dp[i][j][1] += a[i][a[i][0]];
            }

            // 分支2
            dp[i][j][0] = std::max(dp[i][j][0], dp[i - 1][j][0]);
            dp[i][j][1] = std::max(dp[i][j][1], dp[i - 1][j][1]);

            // 分支3
            for (int k = 1; k < a[i][0]; k++) {
                if (j >= k) {
                    dp[i][j][1] = std::max(dp[i][j][1], dp[i - 1][j - k][0] + a[i][k]);
                }
            }
        }
    }

    std::cout << (sum <= k ? dp[n][sum][0] : std::max(dp[n][k][0], dp[n][k][1])) << '\n';
    return;
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
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18, T = 1e12;
constexpr int N = 1e2, X = 1e9;

void solve()
{
    int n = 0, k = 0;
    i64 x = 0;
    std::cin >> n >> k >> x;
    std::vector<i64> t(n + 1, 0), pre(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> t[i];
        pre[i] = pre[i - 1] + t[i];
    }

    // efficient moment
    std::vector clk(1, -Inf);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            clk.push_back(t[i] + x * j);
        }
    }
    std::sort(clk.begin(), clk.end());
    clk.erase(std::unique(clk.begin(), clk.end()), clk.end());
    int T = clk.size() - 1;
    std::vector lst(T + 1, 0ll);
    int p = 1, q = 0;
    while (p <= T) {
        while (clk[q] + x <= clk[p]) {
            q++;
        }
        lst[p] = q - 1;
        p++;
    }

    // dp[i][j] minimal dissatisfaction of clk[i] when having shipped j orders
    std::vector dp(T + 1, std::vector(n + 1, Inf));
    for (int i = 0; i <= T; i++) {
        dp[i][0] = 0;
    }
    for (int i = 1; i <= T; i++) {
        for (int j = 1; j <= n && t[j] <= clk[i]; j++) {
            // do nothing at clk[i]
            dp[i][j] = dp[i - 1][j];

            // ship orders at clk[i]
            for (int num = 1; num <= k && j - num >= 0; num++) {
                dp[i][j] = std::min(dp[i][j], dp[lst[i]][j - num] + clk[i] * num - (pre[j] - pre[j - num]));
            }
        }
    }
    
    i64 ans = Inf;
    for (int i = 1; i <= T; i++) {
        ans = std::min(ans, dp[i][n]);
    }
    std::cout << ans << '\n';
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
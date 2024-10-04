#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7, Inf = 1e18;
constexpr int N = 2e5, M = 1024, P = 1e4;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n + 1, 0);
    std::vector p(n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    
    i64 f = 285700002;
    for (int i = 1; i <= n; i++) {
        std::cin >> p[i];
        p[i] = p[i] * f % Mod; 
    }

    // dp[k][i][j][s]
    std::vector dp(2, std::vector(10, std::vector(10, std::vector(4, 0ll))));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            dp[0][i][j][0] = 1;
        }
    }
    for (int k = 1, id = 1; k <= n; k++, id ^= 1) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                int t = ((a[k] >> i & 1) << 1) | (a[k] >> j & 1);
                for (int s = 0; s < 4; s++) {
                    dp[id][i][j][s] = ((1ll - p[k] + Mod) * dp[id ^ 1][i][j][s] + p[k] * dp[id ^ 1][i][j][s ^ t]) % Mod;
                }
            }
        }
    }

    i64 ans = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            ans = (ans + (1ll << i + j) * dp[n & 1][i][j][3]) % Mod;
        }
    }
    std::cout << ans << '\n';
}

int main()
{
    // IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
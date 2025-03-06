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
constexpr int N = 10, M = 100, Inf = 1e9;

void solve()
{
    int n = 0, m = 0;
    std::string s;
    std::cin >> n >> m >> s;
    s = "#" + s;

    std::vector f(m + 1, std::vector(1 << n, 0ll));
    std::vector pre(n + 1, 0), dp(n + 1, 0);
    f[0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < (1 << n); j++) {
            if (f[i][j] == 0) {
                continue;
            }
            for (int k = 0; k < n; k++) {
                if (j >> k & 1) {
                    pre[k + 1] = pre[k] + 1;
                } else {
                    pre[k + 1] = pre[k];
                }
            }

            for (int c = 0; c < 26; c++) {
                for (int k = 1; k <= n; k++) {
                    if (c == s[k] - 'a') {
                        dp[k] = pre[k - 1] + 1;
                    } else {
                        dp[k] = std::max(pre[k], dp[k - 1]);
                    }
                }
                
                int state = 0;
                for (int k = 0; k < n; k++) {
                    if (dp[k] < dp[k + 1]) {
                        state |= 1 << k;
                    }
                }
                (f[i + 1][state] += f[i][j]) %= Mod;
            }
        }
    }

    std::vector ans(n + 1, 0ll);
    for (int u = 0; u < (1 << n); u++) {
        (ans[__builtin_popcount(u)] += f[m][u]) %= Mod;
    }
    for (int i = 0; i <= n; i++) {
        std::cout << ans[i] << " \n"[i == n];
    }
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
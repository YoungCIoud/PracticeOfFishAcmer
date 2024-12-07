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

void solve()
{
    std::string a, b, c;
    std::cin >> a >> b >> c;
    a = "#" + a;
    b = "#" + b;
    c = "#" + c;
    if (a.length() > b.length()) {
        std::swap(a, b);
    }
    int n = a.length() - 1;
    int m = b.length() - 1;
    // dp[i][j] c里前i个字符有j个在a里时的最小值
    std::vector dp(n + m + 1, std::vector(n + 1, Inf));
    dp[0][0] = 0;
    for (int i = 1; i <= n + m; i++) {
        int mn = std::max(0, i - m), mx = std::min(n, i);
        // dp[i - 1][j - 1] dp[i - 1][j]
        for (int j = mn; j <= mx; j++) {
            // 当前字符是b里的
            if (i - j != 0) {
                dp[i][j] = dp[i - 1][j] + (c[i] != b[i - j]);
            }
            // 当前字符是a里的
            if (j != 0) {
                dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1] + (c[i] != a[j]));
            }
        }
    }

    std::cout << dp[n + m][n] << '\n';
    return;
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
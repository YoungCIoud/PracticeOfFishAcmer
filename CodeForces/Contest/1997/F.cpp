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
constexpr int N = 1e3, X = 10, Inf = 1e9, L = 26;

std::vector dp(89 * N + 1, std::vector(N + 1, 0));

void solve()
{
    int n = 0, x = 0, m = 0;
    std::cin >> n >> x >> m;

    std::vector<int> fab(L + 1, 1);
    for (int i = 3; i <= L; i++) {
        fab[i] = fab[i - 1] + fab[i - 2];
    }

    dp[0][0] = 1;
    for (int k = 1; k <= x; k++) {
        for (int i = fab[k]; i <= n * fab[k]; i++) {
            for (int j = 1; j <= n; j++) {
                (dp[i][j] += dp[i - fab[k]][j - 1]) %= Mod;
            }
        }
    }

    std::vector<int> mn(n * fab[x] + 1, Inf);
    mn[0] = 0;
    for (int i = 1; i <= L; i++) {
        for (int j = fab[i]; j <= n * fab[x]; j++) {
            mn[j] = std::min(mn[j], mn[j - fab[i]] + 1);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n * fab[x]; i++) {
        if (mn[i] == m) {
            (ans += dp[i][n]) %= Mod;
        }
    }
    std::cout << ans << '\n';
    
    return;
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
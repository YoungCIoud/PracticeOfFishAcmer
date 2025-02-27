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
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::vector a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::vector qr(n + 1, std::vector<std::array<int, 2>>{});
    for (int i = 0; i < q; i++) {
        int r = 0, x = 0;
        std::cin >> r >> x;
        qr[r].push_back({ x, i });
    }

    std::vector dp(n + 1, Inf + 5), ans(q, 0);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[std::lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin()] = a[i];
        for (auto &[mx, idx] : qr[i]) {
            ans[idx] = std::upper_bound(dp.begin(), dp.end(), mx) - dp.begin() - 1;
        }
    }

    for (auto &i : ans) {
        std::cout << i << '\n';
    }
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
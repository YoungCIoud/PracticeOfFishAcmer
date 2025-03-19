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
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr u64 Mod = 1'0000'0000'0000'1029, MAX = -1;
constexpr int N = 5e5, Q = 5e5;

void solve() {
    int n = 0;
    std::cin >> n;
    std::vector gate(n, std::array<std::pair<char, int>, 2>{});
    std::vector dp(n, std::array<i64, 2>{});
    for (auto &[u, v] : gate) {
        std::cin >> u.first >> u.second >> v.first >> v.second;
    }
    for (int i = 0; i < n; i++) {
        dp[i][0] = gate[i][0].first == '+' ? 1 : gate[i][0].second;
        dp[i][1] = gate[i][1].first == '+' ? 1 : gate[i][1].second;
    }
    dp.push_back({ 1, 1 });
    i64 ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 2; j++) {
            int res = dp[i][j] - 1;
            if (dp[i][j] == 1) {
                ans += 1ll * gate[i][j].second * std::max(dp[i + 1][0], dp[i + 1][1]);
            }
            dp[i][j] = dp[i + 1][j] + 1ll * res * std::max(dp[i + 1][0], dp[i + 1][1]);
        }
    }
    std::cout << ans + dp[0][0] + dp[0][1] << '\n';
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
    return 0;
}

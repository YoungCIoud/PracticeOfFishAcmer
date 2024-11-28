#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    #define cout cout << ">>>\t"
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
    int h = 0, w = 0;
    std::cin >> h >> w;
    std::vector g(h, std::string{});
    for (auto &s : g) {
        std::cin >> s;
    }
    // 转置 使 w 是较小值
    if (w > h) {
        std::vector _g(w, std::string(h, ' '));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                _g[j][i] = g[i][j];
            }
        }
        g = _g;
        std::swap(h, w);
    }

    std::unordered_map<int, i64> dp; // status val
    dp[0] = 1;
    const int full = (1 << 2 * w) - 1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            std::unordered_map<int, i64> tmp;
            for (auto const &[s, v] : dp) {
                int lst = j ? (s & 3) : 0;
                int fst = s >> (2 * (w - 1)) & 3;
                // 枚举当前位置放的数字
                for (int k = 1; k <= 3; k++) {
                    if ((g[i][j] == k + '0' || g[i][j] == '?') && k != lst && k != fst) {
                        (tmp[(s << 2 | k) & full] += v) %= Mod;
                    }
                }
            }
            dp = tmp;
        }
    }

    i64 ans = 0;
    for (auto const &[s, v] : dp) {
        (ans += v) %= Mod;
    }
    std::cout << ans << '\n';
    return;
}


int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
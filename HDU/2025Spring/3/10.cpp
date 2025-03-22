#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e6, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector d1(n, 0ll), d2(n, 0ll), d3(n, 0ll), d4(n, 0ll);
    for (int i = 0; i < n; i++) {
        i64 x = 0, y = 0;
        std::cin >> x >> y;
        d1[i] = x + y;
        d2[i] = x + Inf - y;
        d3[i] = Inf - x + Inf - y;
        d4[i] = Inf - x + y;
    }
    std::sort(d1.begin(), d1.end());
    std::sort(d2.begin(), d2.end());
    std::sort(d3.begin(), d3.end());
    std::sort(d4.begin(), d4.end());

    i64 ans = 2 * Inf;
    for (int i = 0; i < m; i++) {
        i64 x = 0, y = 0;
        std::cin >> x >> y;
        ans = std::min( ans, std::max({ abs(d1.back() - (x + y)), abs(d2.back() - (x + Inf - y)), abs(d3.back() - (Inf - x + Inf - y)), abs(d4.back() - (Inf - x + y)) }));
    }
    std::cout << ans << '\n';
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
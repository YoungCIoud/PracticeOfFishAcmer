#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    i64 h = 0, m = 0, a = 0;
    std::cin >> h >> m >> a;
    i64 ans = 0;
    if (a * 2ll == h * m) {
        ans = h * m;
    }
    else {
        i64 g = std::__gcd(h - 1, h * m);
        ans = g * (a / g * 2ll + 1ll);
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
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e9;

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;

    if (k == 1) {
        std::cout << n << '\n';
        return;
    }

    int mx = 1;
    while (1ll * mx * k <= n) {
        mx *= k;
    }

    int ans = 0;
    for (; n && mx; mx /= k) {
        ans += n / mx;
        n %= mx;
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
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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 2e5, MAX = 1e9;

void solve() {
    i64 x = 0;
    i64 m = 0, ans = 0;
    std::cin >> x >> m;

    // y = kx ^ x
    i64 p = 1ll * (m ^ x) / x;
    i64 l = std::max(0ll, p - 10ll);
    ans = l;
    if (l > 1) {
        ans--;
    }
    for (int i = 0; i < 20; i++) {
        i64 y = (l + i) * x ^ x;
        if (1 <= y && y <= m) {
            ans++;
        }
    }

    for (int y = 1; y <= std::min(m, x); y++) {
        if ((x ^ y) % y == 0 && (x ^ y) % x != 0) {
            ans++;
        } 
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
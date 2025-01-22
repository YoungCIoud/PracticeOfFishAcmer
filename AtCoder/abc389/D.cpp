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
    int r = 0;
    std::cin >> r;

    i64 ans = 0;
    for (int i = 1, j = r - 1; i < r; i++) {
        while (1ll * (2 * j + 1) * (2 * j + 1) + 1ll * (2 * i + 1) * (2 * i + 1) > 4ll * r * r) {
            j--;
        }
        ans += j;
    }
    ans *= 4;
    ans += 4 * (r - 1) + 1;
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
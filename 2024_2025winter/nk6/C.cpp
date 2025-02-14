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
    i64 k = 0;
    std::cin >> k;
    k--;
    if (k == 0) {
        std::cout << 2 << '\n';
        return;
    }

    int l = 1, r = 62;
    while (l <= r) {
        int m = l + r >> 1;
        if ((1ull << m) < k + m + 1ll) {
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }
    // std::cout << r << ' ' << l << '\n';
    k -= (1ull << r) - r - 1;
    std::cout << (1ull << l) + (k << 1) << '\n';
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
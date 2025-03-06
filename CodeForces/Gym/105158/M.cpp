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
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0ll), b(n, 0ll);
    for (auto &i : a) {
        std::cin >> i;
    }
    for (auto &i : b) {
        std::cin >> i;
    }

    i64 l = 0, r = Inf;
    while (l <= r) {
        i64 m = l + r >> 1;
        i64 L = 0, R = 2ll * Inf;
        for (int i = 0; i < n; i++) {
            L = std::max(L, a[i] - m * b[i]);
            R = std::min(R, a[i] + m * b[i]);
        }

        if (L <= R) {
            r = m - 1;
        }
        else {
            l = m + 1;
        }
    }
    std::cout << l << '\n';
    return;
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
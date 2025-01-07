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
    i64 l = 0, r = 0, G = 0;
    std::cin >> l >> r >> G;
    l = (l + G - 1) / G;
    r /= G;

    for (i64 i = r - l; i >= 0; i--) {
        for (i64 j = l; j + i <= r; j++) {
            if (std::__gcd(j, j + i) == 1) {
                std::cout << j * G << ' ' << (j + i) * G << '\n';
                return;
            }
        }
    }
    std::cout << "-1 -1\n";
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
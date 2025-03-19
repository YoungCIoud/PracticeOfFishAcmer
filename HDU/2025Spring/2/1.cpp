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
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::vector mn(64, MAX);
    for (int i = 0; i < n; i++) {
        u64 a = 0;
        std::cin >> a;
        for (int i = 0; i < 64; i++) {
            if (a >> i & 1) {
                mn[i] &= a;
            }
        }
    }

    u64 ans = 0;
    while (q--) {
        u64 x = 0;
        std::cin >> x;
        u64 res = MAX, cur = 0;
        for (int i = 63; ~i; i--) {
            if (x >> i & 1) {
                cur |= mn[i];
            }
            else {
                res = std::min(res, cur | mn[i]);
            }
        }
        ans ^= (std::min(res, cur) % Mod);
    }
    std::cout << ans << '\n';
}

int main()
{
    // IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }
    return 0;
}

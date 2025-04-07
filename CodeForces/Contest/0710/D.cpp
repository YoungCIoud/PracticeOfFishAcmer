#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), \
                std::cin.tie(0), \
                std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

i64 solve()
{
    i64 k1 = 0, a1 = 0, k2 = 0, a2 = 0, l = 0, r = 0;
    std::cin >> k1 >> a1 >> k2 >> a2 >> l >> r;
    l = std::max({ l, a1, a2 });
    if (l > r) {
        return 0;
    }

    if (k1 < k2) {
        std::swap(k1, k2);
        std::swap(a1, a2);
    }
    
    i64 sum = 0;
    if (k1 * k1 >= (r - l + 1)) {
        for (i64 i = (l - a1 + k1 - 1) / k1 * k1 + a1; i <= r; i += k1) {
            if ((i - a2) % k2 == 0) {
                sum++;
            }
        }
    }
    else {
        i64 lcm = k1 * k2 / std::__gcd(k1, k2);
        for (i64 i = a1; i < std::min(r + 1, a1 + lcm); i += k1) {
            if ((i - a2) % k2) {
                continue;
            }

            i64 L = std::max(0ll, (l - i + lcm - 1) / lcm) * lcm + i;
            sum += (r - L) / lcm + 1;
        }
    }

    return sum;
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        std::cout << solve() << '\n';
    }

    sp();

    return 0;
}
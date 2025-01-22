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

constexpr i64 Mod = 998244353, M = 1e18, Inf = 3e9;
constexpr int N = 2e5, P = 2e9;

void solve()
{
    int n = 0;
    i64 m = 0;
    std::cin >> n >> m;
    std::vector p(n, 0ll);
    for (auto &i : p) {
        std::cin >> i;
    }

    // binary search the upper_bound price (2k - 1)p;
    i64 l = 0ll, r = m;
    auto chk = [&](i64 up) -> bool {
        i128 tot = 0;
        for (auto &i : p) {
            i128 k = (up + i) / (2ll * i);
            tot += k * k * i;
            if (tot > m) {
                return false;
            }
        }
        return true;
    };
    while (l <= r) {
        i64 mid = r + l >> 1;
        if (chk(mid)) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }

    i64 ans = 0, sum = 0;
    for (auto &i : p) {
        i64 k = (r + i) / (2ll * i);
        ans += k;
        sum += k * k * i;
    }
    std::cout << ans + (m - sum) / l << '\n';
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
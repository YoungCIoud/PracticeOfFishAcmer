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
constexpr int N = 1e5, M = 1e5, Inf = 2e9;

void solve()
{
    int n = 0, x = 0;
    std::cin >> n >> x;
    std::vector U(n, 0ll), D(n, 0ll);
    for (int i = 0; i < n; i++) {
        std::cin >> U[i] >> D[i];
    }

    i64 l = 1, r = Inf;
    for (int i = 0; i < n; i++) {
        r = std::min(r, U[i] + D[i]);
    }
    while (l <= r) {
        i64 m = l + r >> 1; 
        
        i64 L = 0, R = Inf;
        for (int i = 0; i < n; i++) {
            L = std::max(L - x, std::max(0ll, m - D[i]));
            R = std::min(R + x, std::min(m, U[i]));
            if (L > R) { 
                break;
            }
        }

        if (L <= R) {
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }
    
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        ans += U[i] + D[i] - r;
    }
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
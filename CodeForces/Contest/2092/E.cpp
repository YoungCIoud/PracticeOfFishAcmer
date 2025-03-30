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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e9, M = 1e9, K = 2e5;

i64 qpow(i64 a, i64 p) {
    i64 res = 1;
    while (p) {
        if (p & 1) {
            (res *= a) %= Mod;
        }
        
        (a *= a) %= Mod;
        p >>= 1;
    }
    return res;
}

void solve()
{
    i64 n = 0, m = 0;
    int k = 0;
    std::cin >> n >> m >> k;

    std::array<i64, 3> cr { 0, 0, (m - 2) << 1 };
    std::array<i64, 3> cc { 0, 0, (n - 2) << 1 };
    int ca = 4;
    i64 ce = 1ll * (n - 2) * (m - 2);
    for (int i = 0; i < k; i++) {
        int x = 0, y = 0, t = 0;
        std::cin >> x >> y >> t;
        if (x == 1 && y == 1 || x == 1 && y == m || x == n && y == 1 || x == n && y == m) {
            ca--;
        }
        else if (x == 1 || x == n) {
            cr[2]--;
            cr[t]++;
        }
        else if (y == 1 || y == m) {
            cc[2]--;
            cc[t]++;
        }
        else {
            ce--;
        }
    }

    if (cr[2] == 0 && cc[2] == 0 && (cr[0] + cc[0]) % 2) {
        std::cout << 0 << '\n';
    }
    else {
        std::cout << qpow(2, ce + ca + std::max(cc[2] + cr[2] - 1, 0ll)) << '\n';
    }

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
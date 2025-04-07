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
i64 inv(i64 a) {
    return qpow(a, Mod - 2);
}

void solve()
{
    int n = 0;
    std::cin >> n;
    int k = n / 5, m = n % 5;
    i64 ans = 0;
    if (m == 0 || m == 2) {
        ans = 1;
    }
    else if (m == 1) {
        ans = Mod - inv(qpow(2, std::max(1, k))) + 1;
    }
    else if (m == 3) {
        ans = Mod - inv(qpow(2, k + 2)) + 1; 
    }
    else {
        ans = Mod - inv(qpow(2, k + 1)) + 1;
    }
    std::cout << ans << '\n';
    // std::vector<double> p = { 1, 0.5, 1, 0.75, 0.5, 1, 0.5, 1 };
    // for (int i = 8; i < 100; i++) {
    //     p.push_back(0.5 * (std::max(p[i - 2], p[i - 5]) + std::max(p[i - 8], p[i - 5])));
    // }
    // for (int i = 0; i < 100; i++) {
    //     if (i % 5 == 0) {
    //         std::cout << "\n";
    //     }
    //     std::cout << i << '\t' <<  p[i] << '\n';
    // }
    // return;
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
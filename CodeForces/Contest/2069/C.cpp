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
    std::array<i64, 4> f = { 0, 0, 0, 0 };
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        if (a == 1) {
            (f[1] += 1) %= Mod;
        }
        else if (a == 2) {
            (f[2] <<= 1ll) %= Mod;
            (f[2] += f[1]) %= Mod;
        }
        else {
            (f[3] += f[2]) %= Mod;
        }
    }
    std::cout << f[3] << '\n';
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
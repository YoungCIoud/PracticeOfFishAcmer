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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        a[0] += a[i];
        if (a[0] >= Mod) {
            a[0] -= Mod;
        }
    }
    
    i64 S = 0;
    for (int i = 1; i <= n; i++) {
        a[0] -= a[i];
        if (a[0] < 0) {
            a[0] += Mod;
        }
        (S += a[0] * a[i] % Mod) %= Mod;
    }

    i64 M = 1;
    for (int i = n; i >= 2; i--) {
        (M *= 1ll * i * (i - 1) / 2 % Mod) %= Mod;
    }
    std::cout << S << ' ' << M << '\n';
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
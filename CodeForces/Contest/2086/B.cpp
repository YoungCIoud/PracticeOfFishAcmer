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

void solve()
{
    int n = 0, k = 0;
    i64 x = 0;
    std::cin >> n >> k >> x;
    std::vector a(n + 1, 0ll);
    for (int i = n; i >= 1; i--) {
        std::cin >> a[i];
        a[0] += a[i];
    }

    int rep = (x - 1) / a[0];
    x -= a[0] * rep;
    int num = 0;
    x -= a[1];
    while (x > 0) {
        num++;
        x -= a[num + 1];
    }
    std::cout << std::max(0ll, 1ll * n * k - (1ll * rep * n + num)) << '\n';
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
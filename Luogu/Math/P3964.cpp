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

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector p(n + 1, std::array<i64, 2>{});
    std::vector x(n + 1, 0ll), y(n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        double a = 0.0, b = 0.0;
        std::cin >> a >> b;
        x[i] = a + b;
        y[i] = a - b;
        p[i] = { x[i], y[i] };
    }
    
    std::sort(x.begin() + 1, x.end());
    std::sort(y.begin() + 1, y.end());
    std::vector prex(x), prey(y);
    for (int i = 1; i <= n; i++) {
        prex[i] += prex[i - 1];
        prey[i] += prey[i - 1];
    }

    i64 ans = Inf;
    x[0] = y[0] = -Inf;
    for (int i = 1; i <= n; i++) {
        i64 res = 0;
        int px = std::lower_bound(x.begin(), x.end(), p[i][0]) - x.begin();
        res += 1ll * px * p[i][0] - prex[px] + (prex[n] - prex[px]) - 1ll * (n - px) * p[i][0];
        int py = std::lower_bound(y.begin(), y.end(), p[i][1]) - y.begin();
        res += 1ll * py * p[i][1] - prey[py] + (prey[n] - prey[py]) - 1ll * (n - py) * p[i][1];
        ans = std::min(ans, res);
    }

    std::cout << ans / 2 << '\n';
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
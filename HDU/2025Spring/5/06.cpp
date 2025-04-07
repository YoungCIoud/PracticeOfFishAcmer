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

double dis(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void solve()
{
    int d = 0, r = 0, x = 0, y = 0;
    std::cin >> d >> r >> x >> y;
    double ans = 0;
    if (-d <= y && y <= d) {
        ans = std::min(std::abs(x - r), std::abs(x + r));
    }
    else if (y > 0) {
        ans = std::abs(dis(0, d, x, y) - r);
    }
    else {
        ans = std::abs(dis(0, -d, x, y) - r);
    }
    std::cout << std::fixed << std::setprecision(0) << ans << '\n';
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
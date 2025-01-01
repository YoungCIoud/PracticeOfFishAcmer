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
#define Pi M_PI

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 100, M = 1e5, Inf = 1e9;
constexpr double eps = 10-10;

// (0, 0) 为圆心， r 为半径
// 求圆外一点到圆的切线的夹角
std::vector<double> angle(int r, int x, int y) {
    std::vector<double> res;
    if (x == r || x == -r) {
        res.push_back(y < 0 ? 3.0 * M_PI_2 : M_PI_2);
        double tmp = M_PI_2 - 2.0 * atan2(r, abs(y));

    }

    return res;
}

void solve()
{
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
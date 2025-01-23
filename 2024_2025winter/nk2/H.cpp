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
    int a = 0, b = 0, c = 0, d = 0;
    std::cin >> a >> b >> c >> d;
    std::cout << b << ' ' << d << '\n';
    int w = b - a, h = d - c;
    if (w >= h) {
        std::cout << b - 1 << ' ' << d << '\n';
        std::cout << a << ' ' << d - 1 << '\n';
    }
    else {
        std::cout << b << ' ' << d - 1 << '\n';
        std::cout << b - 1 << ' ' << c << '\n';
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
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
    i64 x = 0;
    char c = '\000';
    std::cin >> x >> c;
    i64 a = 0, b = 0;
    if (c == '*') {
        a = x, b = 1;
    }
    else if (c == '+') {
        a = x - 1ll, b = 1;
    }
    else {
        a = x + 1ll, b = 1;
    }
    std::cout << a << ' ' << b << '\n';
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
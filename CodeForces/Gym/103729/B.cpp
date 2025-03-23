#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;
// using namespace std;
constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

i64 lowbit(i64 x) {
    return x & -x;
}

void solve()
{
    i64 x = 0, y = 0;
    int a = 0, b = 0;
    std::cin >> x >> y >> a >> b;
    i64 g = std::__gcd(x, y);
    x /= g, y /= g;
    if (x + y != lowbit(x + y)) {
        std::cout << -1 << '\n';
    }
    else {
        // int g = std::min(lowbit(x), lowbit(y));
        std::cout << std::log2(lowbit(x + y)) + 1 << '\n';
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

    system("pause");

    return 0;
}
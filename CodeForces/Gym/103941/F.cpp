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
    if (n & 1) {
        n = n + 1 >> 1;
        std::cout << n << '\n';
        for (int i = 1; i <= n; i++) {
            std::cout << i << ' ';
        }
    }
    else if (n > 4) {
        n >>= 1;
        std::cout << n << '\n';
        n++;
        std::cout << 1 << ' ';
        for (int i = 3; i <= n; i++) {
            std::cout << i << ' ';
        }
    }
    else {
        std::cout << -1;
    }
    std::cout << '\n';
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
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

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    if (n == 1) {
        std::cout << "1\n1\n";
    }
    else if (n == 2) {
        std::cout << "2\n2 2\n";
    }
    else {
        std::cout << 2 * (n - 2) << '\n';
        for (int i = 2; i <= n - 1; i++) {
            std::cout << i << ' ';
        }
        for (int i = n - 1; i >= 2; i--) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
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

    return 0;
}
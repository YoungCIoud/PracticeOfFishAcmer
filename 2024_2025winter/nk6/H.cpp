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
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector s(m, std::array<int, 3>{});
    
    for (auto &[l, r, c] : s) {
        std::cin >> l >> r >> c;
    }
    if ((s[0][1] - s[0][0]) % 2 == 1) {
        for (int i = n; i >= 1; i--) {
            std::cout << i << " \n"[i == 1];
        }
    }
    else {
        std::cout << n << ' ';
        for (int i = n - 1; i >= 2; i -= 2) {
            std::cout << i - 1 << ' ' << i << ' ';
        }
        if (n % 2 == 0) {
            std::cout << 1 << ' ';
        }
        std::cout << '\n';
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
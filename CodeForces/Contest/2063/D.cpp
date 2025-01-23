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
    std::vector a(n, 0), b(m, 0);
    for (auto &i : a) {
        std::cin >> i;
    }
    for (auto &i : b) {
        std::cin >> i;
    }
    if (n < m) {
        std::swap(n, m);
        std::swap(a, b);
    }

    int d = n - m, k = 0;
    if (d >= m) {
        k = m;
    }
    else {
        k = d + (m - d) / 3 * 2;
    }
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
/*
5
1 3
0
0 1 -1
2 4
0 100
-100 -50 0 50
2 4
0 1000
-100 -50 0 50
6 6
20 1 27 100 43 42
100 84 1 24 22 77
8 2
564040265 -509489796 469913620 198872582 -400714529 553177666 131159391 -20796763
-1000000000 1000000000

1
2
2
150 200
2
1000 200
4
99 198 260 283
2
2000000000 2027422256
*/
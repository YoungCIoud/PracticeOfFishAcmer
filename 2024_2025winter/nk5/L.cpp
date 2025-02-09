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
    int ans = n / 6;
    if (n <= 3) {
        std::cout << 0 << '\n';
    }
    else if (n % 6 == 3) {
        std::cout << ans * 2 + 1 << '\n';
        std::cout << 1 << ' ' << 3 << ' ' << n << '\n';
        std::cout << 2 << ' ' << 4 << ' ' << 5 << '\n';
        std::cout << n - 1 << ' ' << n - 2 << ' ' << n - 3 << '\n';
        for (int i = 6; i < n - 3; i += 6) {
            std::cout << i << ' ' << i + 1 << ' ' << i + 3 << '\n';
            std::cout << i + 2 << ' ' << i + 4 << ' ' << i + 5 << '\n';
        }
    }
    else {
        int d = 0;
        if (n % 6 >= 4) {
            d = 1;
        }
        std::cout << ans * 2 + d << '\n';
        for (int i = 1; i < ans * 6; i += 6) {
            std::cout << i << ' ' << i + 1 << ' ' << i + 3 << '\n';
            std::cout << i + 2 << ' ' << i + 4 << ' ' << i + 5 << '\n';
        }
        if (d == 1) {
            int i = ans * 6 + 1;
            std::cout << i << ' ' << i + 1 << ' ' << i + 3 << '\n';
        }
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

/*
33
1 2 4
3 5 6
7 8 10
9 11 12
13 14 16
15 17 18
19 20 22
21 23 24
25 26 28
27 29 30
31 32 34
33 35 36
37 38 40
39 41 42
43 44 46
45 47 48
49 50 52
51 53 54
55 56 58
57 59 60
61 62 64
63 65 66
67 68 70
69 71 72
73 74 76
75 77 78
79 80 82
81 83 84
85 86 88
87 89 90
91 92 94
93 95 96
97 98 100
97 98 100
*/
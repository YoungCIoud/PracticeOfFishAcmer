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
constexpr int N = 1e3, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector a(n + 1, std::vector(k + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            std::cin >> a[i][j];
        }
    }

    std::vector f(n + 1, std::vector(k + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            f[i][j] = f[i - 1][j] + a[i][j];
        }
        for (int j = 1; j <= k; j++) {
            f[i][j] = std::max(f[i][j], f[i][j - 1]);
        }
    }
    std::cout << f[n][k] << '\n';
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
1
5 3
1 10 2
1 10 2
1 10 2
1 2 10
1 2 10
*/
#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), \
                std::cin.tie(0), \
                std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 400, M = 1e5, Inf = 1e9;

int p[400];
i64 f[N + 5][N + 5];

void solve()
{
    int n = 0, m = 0, v = 0;
    std::cin >> n >> m >> v;
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= v; j++) {
            f[i][j] = 0;
        }
    }

    f[0][0] = 1;
    for (int k = 0; k < n; k++) {
        for (int i = 1; i <= m; i++) {
            for (int j = p[k]; j <= v; j++) {
                (f[i][j] += f[i - 1][j - p[k]]) %= Mod;
            }
        }
    }
    
    i64 ans = 0;
    for (int j = 1; j <= v; j++) {
        (ans += f[m][j]) %= Mod;
    }
    std::cout << ans << '\n';
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
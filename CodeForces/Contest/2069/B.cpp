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
    std::vector col(n * m + 1, 0);
    std::vector g(n, std::vector(m, 0));
    for (auto &v : g) {
        for (auto &i : v) {
            std::cin >> i;
            col[i] = 1;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (g[i][j] == g[i - 1][j] || g[i][j] == g[i][j - 1]) {
                col[g[i][j]] = 2;
            }
        }
    }
    for (int j = 1; j < m; j++) {
        if (g[0][j] == g[0][j - 1]) {
            col[g[0][j]] = 2;
        }
    }
    for (int i = 1; i < n; i++) {
        if (g[i][0] == g[i - 1][0]) {
            col[g[i][0]] = 2;
        }
    }

    int ans = 0, mx = 0;
    for (int i = 1; i <= m * n; i++) {
        ans += col[i];
        mx = std::max(mx, col[i]);
    }

    std::cout << ans - mx << '\n';
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
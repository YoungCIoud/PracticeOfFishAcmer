#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e15;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0, m = 0, q = 0;
    std::cin >> n >> m >> q;
    std::vector a(m + 1, 0), b(m + 1, 0), c(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        std::cin >> a[i] >> b[i] >> c[i];
    }
    std::vector op(m + 1, true);
    std::stack<std::array<int, 2>> qr;
    while (q--) {
        std::array<int, 2> t = { 0, 0 };
        int ope = 0;
        std::cin >> ope >> t[0];
        if (ope == 2) {
            std::cin >> t[1];
        }
        else {
            op[t[0]] = false;
        }
        qr.push(t);
    }

    std::vector g(n + 1, std::vector(n + 1, Inf));
    for (int i = 1; i <= n; i++) {
        g[i][i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        if (op[i]) {
            g[a[i]][b[i]] = g[b[i]][a[i]] = c[i];
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                    g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    std::stack<i64> ans;
    while (not qr.empty()) {
        auto [x, y] = qr.top();
        qr.pop();
        
        if (y == 0) {
            if (g[a[x]][b[x]] <= 1ll * c[x]) {
                continue;
            }
            else {
                g[a[x]][b[x]] = 1ll * c[x];
                g[b[x]][a[x]] = 1ll * c[x];
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        g[i][j] = std::min({ g[i][j], g[i][a[x]] + g[a[x]][b[x]] + g[b[x]][j], g[i][b[x]] + g[b[x]][a[x]] + g[a[x]][j] });
                    }
                }
            }
        }
        else {
            ans.push((g[x][y] == Inf ? -1 : g[x][y]));
        }
    }

    while (not ans.empty()) {
        std::cout << ans.top() << '\n';
        ans.pop();
    }
    return;
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
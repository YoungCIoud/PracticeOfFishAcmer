#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 100, M = 1e5;

void solve()
{
    std::vector g(N + 1, std::vector<bool>(N + 1, false));
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        int x = 0, y = 0;
        std::cin >> x >> y;
        g[x][y] = true;
    }

    int cnt = 0;
    double ans = 0;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (g[i][j]) {
                ans += 2.0;
                for (int u = 0; u < 2; u++) {
                    if (g[i][j + (u ? 1 : -1)]) {
                        cnt++;
                    }
                    if (g[i + (u ? 1 : -1)][j]) {
                        cnt++;
                    }
                }
            }
        }
    }
    
    std::cout << ans - (double)cnt / 4.0 << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
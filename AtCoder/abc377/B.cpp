#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 8, M = 1e5;

void solve()
{
    std::vector g(8, std::string{});
    for (auto &s : g) {
        std::cin >> s;
    }
    auto gg = g;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (g[i][j] == '#')
            for (int k = 0; k < 8; k++) {
                gg[i][k] = gg[k][j] = '#';
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (gg[i][j] == '.') {
                ans++;
            }
        }
    }
    std::cout << ans << '\n';
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
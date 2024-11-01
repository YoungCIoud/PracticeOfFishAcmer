#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector g(n, std::string{});
    for (auto &s : g) {
        std::cin >> s;
    }
    for (int i = 0; i < n; i++) {
        int rot = (i + 1) % 4;
        while (rot--) {
            for (int j = i; j < n - i - 1; j++) {
                int x = i, y = j;
                char cur = g[i][j];
                for (int k = 0; k < 4; k++) {
                    int nx = y, ny = n - 1 - x;
                    std::swap(cur, g[nx][ny]);
                    x = nx, y = ny;
                }
            }
        }
    }
    for (auto &s : g) {
        std::cout << s << '\n';
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
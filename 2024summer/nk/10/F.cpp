#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1000, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;

    vct vis(n, vct<bool>(n, false));
    vct<ary<int, 2>> pre{};
    for (int i = 0; i < n * n; i++)
    {
        int u = 0, v = 0;
        std::cin >> u >> v;
        u--, v--;

        if (vis[u][v])
        {
            std::cout << 0;
            continue;
        }

        for (auto& [x, y] : pre)
        {
            int dx = x - u, dy = y - v;
            int d = std::__gcd(dx, dy);
            if (dx == 0) dy = 1;
            else if (dy == 0) dx = 1;
            else dx /= d, dy /= d;
            
            for (int tx = u, ty = v; 0 <= tx && tx < n && 0 <= ty && ty < n; tx += dx, ty += dy)
                vis[tx][ty] = true;
            for (int tx = u, ty = v; 0 <= tx && tx < n && 0 <= ty && ty < n; tx -= dx, ty -= dy)
                vis[tx][ty] = true;
        }
        pre.push_back({ u, v });
        std::cout << 1;
    }
    return;
}

int main()
{
    //IOS;
    int t = 1;
    //std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
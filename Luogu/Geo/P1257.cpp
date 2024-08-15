#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

bool in_line(ary<i64, 2> a, ary<i64, 2> b, ary<i64, 2> c)
{
    ary<i64, 2> u = { a[0] - b[0], a[1] - b[1] };
    ary<i64, 2> v = { c[0] - b[0], c[1] - b[1] };
    return u[0] * v[1] == u[1] * v[0];
}

void solve()
{
    int n = 0;
    std::cin >> n;
    vct<ary<i64, 2>> a(n);
    for (auto& [x, y] : a) std::cin >> x >> y;

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            {
                int res = 2;
                for (int k = j + 1; k < n; k++)
                    if (in_line(a[i], a[j], a[k])) res++;
                ans = std::max(ans, res);
            }
    std::cout << ans << '\n';
    // vct<std::map<ary<i64, 2>, bool>> vis(n);
    // int ans = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = i + 1; j < n; j++)
    //     {
    //         ary<i64, 2> k = slope(a[i], a[j]);
    //         if (vis[i][k]) continue;
            
    //         vis[i][k] = vis[j][k] = true;

    //         int res = 2;
    //         for (int t = j + 1; t < n; t++)
    //             if (slope(a[j], a[t]) == k)
    //             {
    //                 res++;
    //                 vis[t][k] = true;
    //             }

    //         ans = std::max(ans, res);
    //     }
    // }

    // std::cout << ans << '\n';
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
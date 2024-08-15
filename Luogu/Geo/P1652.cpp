#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

typedef ary<int, 3> cir;

bool in(int u, int v, cir c)
{
    return pow(c[0] - u, 2) + pow(c[1] - v, 2) < pow(c[2], 2);
}

void solve()
{
    int n;
    std::cin >> n;

    vct<cir> c(n);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < n; j++)
            std::cin >> c[j][i];
    
    int ans = 0;
    int u = 0, v = 0, a = 0, b = 0;
    std::cin >> u >> v >> a >> b;
    for (int i = 0; i < n; i++)
        ans += in(u, v, c[i]) ^ in(a, b, c[i]);
    std::cout << ans << '\n';
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
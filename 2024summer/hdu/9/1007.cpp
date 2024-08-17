#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    vct<bool> vis(n, false);
    bool ans = false;
    for (int i = 0; i < n; i++)
    {
        int u = 0;
        std::cin >> u;
        u--;
        if (vis[u]) ans = true;
        vis[u] = true;
    }
    for (int i = 0; i < n; i++)
    {
        int u = 0;
        std::cin >> u;
    }

    puts(ans ? "shuishui" : "sha7dow");
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
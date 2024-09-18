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
    vct a(n + 1, vct<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++) std::cin >> a[i][j];
    int cur = 1;
    for (int i = 1; i <= n; i++)
    {
        if (cur >= i) cur = a[cur][i];
        else cur = a[i][cur];
    }
    std::cout << cur << '\n';
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
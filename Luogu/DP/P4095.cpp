#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1000, K = 1000;

void solve()
{
    int n = 0;
    std::cin >> n;
    vct cost(n + 1, 0), val(n + 1, 0), lim(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> cost[i] >> val[i] >> lim[i];
    }

    // 第i个物品不要花费j时取得的最大价值
    vct dp(n + 1, vct<int>(K + 1, 0));
}

int main()
{
    //IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
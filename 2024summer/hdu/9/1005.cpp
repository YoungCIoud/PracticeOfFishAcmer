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
    i64 k = 0, x = 0, y = 0;
    std::cin >> k >> x >> y;
    if (x > y) std::swap(x, y);

    i64 d = (k - 1) / x;
    if ((i128)d * y >= k)
        puts("Yes\nYes");
    else if (d & 1)
        puts("No\nYes");
    else
        puts("Yes\nNo");
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
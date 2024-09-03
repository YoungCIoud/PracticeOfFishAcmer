#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

i64 dis2(i64 x, i64 y, i64 u, i64 v)
{
    return (x - u) * (x - u) + (y - v) * (y - v);
}

void solve()
{
    i64 l = 0, x = 0, y = 0;
    std::cin >> l >> x >> y;
    if (dis2(0, 0, x, y) <= l * l)
    {
        std::cout << "Yes\n" << 0 << '\n';
        return;
    }
    if (dis2(l, 0, x, y) <= l * l)
    {
        std::cout << "Yes\n" << l << '\n';
        return;
    }
    std::cout << "No" << '\n';
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
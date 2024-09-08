#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

int f(int x)
{
    int res = 0;
    while (x)
    {
        res = std::max(res, x % 10);
        x /= 10;
    }
    return res;
}

int solve()
{
    int la = 0, ra = 0;
    int lb = 0, rb = 0;
    std::cin >> la >> ra >> lb >> rb;
    int x = la + lb, y = ra + rb;
    if (y - x >= 9) return 9;

    int mx = 0;
    for (int i = x; i <= y; i++)
        mx = std::max(mx, f(i));
    return mx;
}

int main()
{
    //IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        std::cout << solve() << '\n';
    }

    system("pause");

    return 0;
}
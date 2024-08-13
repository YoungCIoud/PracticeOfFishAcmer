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
    i64 n = 0, m = 0, ans = 0;
    i64 a, b;
    i64 mx = 0;
    std::cin >> n >> m >> a >> b;
    if (n == 1)
    {
        ans = m;
    }
    else if (m == 1)
    {
        ans = n;
    }
    else
    {
        ans = ((n - 1) + (m - 1)) * 2ll;
        if (a == 1 || a == n)
        {
            if (b != 1 && b != m)
                mx = n - 2;
        }
        else if (b == 1 || b == m)
        {
            if (a != 1 && a != n)
                mx = m - 2;
        }
        else
        {
            mx = std::max(m - 2, n - 2);
        }
    }
    std::cout << ans + mx << '\n';
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
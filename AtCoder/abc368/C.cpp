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
    i64 ans = 0;
    for (int i = 0, cur = 1; i < n; i++)
    {
        // std::cout << cur << '\n';

        int a = 0;
        std::cin >> a;
        int t = a / 5;

        a -= 5 * t;
        ans += 3 * t;

        while (a > 0)
        {
            a -= cur ? 1 : 3;
            cur = (cur + 1) % 3;
            ans++;
        }
    }

    std::cout << ans << '\n';
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
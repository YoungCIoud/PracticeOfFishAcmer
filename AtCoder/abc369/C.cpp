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
    vct a(n, 0ll);
    for (auto& i : a) std::cin >> i;

    i64 d = a[1] - a[0], ans = n + (n == 1 ? 0 : 1);
    for (int l = 0, r = 2; r < n; r++)
    {
        if (a[r] - a[r - 1] == d) ans += r - l;
        else ans++, l = r - 1, d = a[r] - a[r -  1];
    }

    std::cout << ans << "\n";
    return;
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
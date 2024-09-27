#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    i64 ans = 0, a = 0;
    std::cin >> n;
    for (int i = 1; i <= n - 2; i++) {
        std::cin >> a;
        ans += a;
    }
    std::cin >> a;
    ans -= a;
    std::cin >> a;
    ans += a;
    std::cout << ans << '\n';
    return;
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
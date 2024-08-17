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
    int n;
    std::cin >> n;
    vct<i64> a(n);
    for (auto& i : a) std::cin >> i;

    i64 ans = 0;
    for (int i = n - 1; i >= 1; i--)
    {
        ans += a[0] * a[i] % Mod * (a[0] + a[i]) % Mod;
        ans %= Mod;
        a[0] = (a[i] + a[0]) % Mod;
    }
    std::cout << ans << '\n';
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
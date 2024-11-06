#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    i64 abs_sum = 0;
    int mx = -Inf, mn = Inf;
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        abs_sum += 1ll * ((a < 0) ? -a : a);

        mx = std::max(mx, a);
        mn = std::min(mn, a);
    }
    if (n == 1) {
        std::cout << mx << '\n';
        return;
    }

    if (mx < 0) {
        std::cout << abs_sum + 2ll * mx << '\n';
    }
    else if (mn > 0) {
        std::cout << abs_sum - 2ll * mn << '\n';
    }
    else {
        std::cout << abs_sum << '\n';
    }
    return;
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
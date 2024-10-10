#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double a = 0;
        std::cin >> a;
        sum += a;
    }
    
    double ans = sum / double(n + 1);
    std::cout << std::fixed << std::setprecision(9) << ans * 2.0 << ' ';
    for (int i = 2; i <= n; i++) {
        std::cout << ans << " \n"[i == n];
    }
    return;
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
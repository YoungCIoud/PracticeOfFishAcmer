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
    std::vector a(n + 1, 0), mx(n + 1, 0), mn(n + 2, Inf);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        mx[i] = std::max(mx[i - 1], a[i]);
    }
    for (int i = n; i >= 1; i--) {
        mn[i] = std::min(a[i], mn[i + 1]);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (mx[i] <= mn[i + 1]) {
            ans++;
        }
    }
    std::cout << ans << '\n';
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
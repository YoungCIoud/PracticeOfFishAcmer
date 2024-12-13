#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0, ans = 0, mx = -Inf;
    std::cin >> n;
    std::vector a(n, std::array<int, 2>{});
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        ans += std::max(a[i][0], a[i][1]);
        mx = std::max(mx, std::min(a[i][1], a[i][0]));
    }
    std::cout << ans + mx << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
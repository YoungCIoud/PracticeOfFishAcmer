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
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector vis(n + 1, false);
    int ans = n;
    for (int i = 0; i < m; i++) {
        int a = 0;
        std::cin >> a;
        if (not vis[a]) {
            vis[a] = true;
            ans--;
        }
    }
    std::cout << ans << '\n';
    for (int i = 1; i <= n; i++) {
        if (not vis[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';

    return;
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
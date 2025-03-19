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
constexpr int N = 1e6, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n + 1, 0), pre(n + 1, 0), suf(n + 2, Inf);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        pre[i] = std::max(pre[i - 1], a[i]);
    }
    for (int i = n; i >= 1; i--) {
        suf[i] = std::min(suf[i + 1], a[i]);
    }

    int ans = 0;
    std::vector vis(n + 1, false);
    for (int k = 1; k <= n; k++) {
        if (vis[k]) {
            continue;
        }

        bool ok = true;
        for (int i = 1; i <= n; i += k) {
            if (pre[i - 1] > suf[i]) {
                ok = false;
                break;
            }
        }

        if (not ok) {
            continue;
        }
        
        for (int i = k; i <= n; i += k) {
            if (not vis[i]) {
                vis[i] = true;
                ans++;
            }
        }
    }

    std::cout << ans << '\n';
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
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
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
        i--;
    }

    std::vector vis(1 << 18, false);
    for (int i = 0; i < n; i++) {
        int s = 0, p = i;
        while (p < n && (s & (1 << a[p])) == 0) {
            s |= (1 << a[p]);
            vis[s] = true;
            p++;
        }
    }

    std::vector len((1 << 18), 0);
    for (int s = 1; s < (1 << 18); s++) {
        len[s] = len[s >> 1] + (s & 1);
    }

    int ans = 0;
    vis[0] = 1;
    for (int s = 0; s < (1 << 18); s++) {
        if (vis[s]) {
            int base = ((1 << 18) - 1) ^ s;
            for (int t = base; t; (t -= 1) &= base) {
                if (vis[t]) {
                    ans = std::max(len[s] + len[t], ans);
                }
            }
        }
    }
    std::cout << ans << '\n';
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
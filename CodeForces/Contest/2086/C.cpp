#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), \
                std::cin.tie(0), \
                std::cout.tie(0)
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
    std::vector a(n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    std::vector rt(n + 1, 0ll), len(n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        if (rt[i] != 0) {
            continue;
        }

        int cur = i;
        do {
            len[i]++;
            rt[cur] = i;
            cur = a[cur];
        } while (cur != i);
    }

    std::vector vis(n + 1, false);
    int ans = 0;
    while (n--) {
        int d = 0;
        std::cin >> d;
        if (not vis[rt[d]]) {
            ans += len[rt[d]];
            vis[rt[d]] = true;
        }
        
        std::cout << ans << ' ';
    }
    std::cout << '\n';
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
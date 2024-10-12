#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    i64 w = 0;
    std::cin >> n >> w;
    std::vector p(n + 1, 1);
    for (int i = 2; i <= n; i++) {
        std::cin >> p[i];
    }

    std::vector dep(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        dep[i] = dep[p[i]] + 1;
    }

    std::vector cnt(n + 1, 0);
    std::vector path(n + 1, std::array<int, 2>{});
    for (int i = 1; i <= n; i++) {
        int u = i, v = i % n + 1;
        if (v != 1) {
            cnt[i] = 1;
            path[v][0] = i;
        }
        v = p[v];
        while (u != v) {
            cnt[i]++;
            path[u][1] = i;
            u = p[u];
        }

    }

    i64 pre = 0;
    int rem = n;
    for (int i = 2; i <= n; i++) {
        int x = 0;
        i64 y = 0;
        std::cin >> x >> y;

        for (int j = 0; j < 2; j++) {
            if (--cnt[path[x][j]] == 0) {
                rem--;
            }
        }

        pre += y;
        std::cout << pre * 2ll + 1ll * rem * (w - pre) << " \n"[i == n];
    }

    std::cout << '\n';
    return;
}

int main()
{
    // IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
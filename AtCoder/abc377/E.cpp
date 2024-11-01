#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

int qpow(int a, i64 p, int mod) {
    int res = 1;
    for (; p; p >>= 1, a = 1ll * a * a % mod) {
        if (p & 1) {
            res = 1ll * res * a % mod;
        }
    }
    return res;
}

void solve()
{
    int n = 0;
    i64 k = 0;
    std::cin >> n >> k;
    std::vector p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> p[i];
    }

    std::vector vis(n + 1, false);
    std::vector ans(n + 1, 0), cyc(0, 0);
    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            continue;
        }

        cyc.clear();
        int cur = i;
        while (not vis[cur]) {
            cyc.push_back(cur);
            vis[cur] = true;
            cur = p[cur];
        }

        int d = qpow(2, k, cyc.size());
        for (int j = 0; j < cyc.size(); j++) {
            ans[cyc[j]] = cyc[(j + d) % cyc.size()];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << " \n"[i == n];
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
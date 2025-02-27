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
constexpr int N = 1e2, M = 1e5, K = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector d(n, std::vector(M + 1, 0));
    for (int i = 0; i < n; i++) {
        std::cin >> d[i][0];
        for (int j = 0; j < d[i][0]; j++) {
            int a = 0;
            std::cin >> a;
            d[i][a]++;
        }
    }

    std::vector cnt(n, std::vector(n, 0ll));
    for (int k = 1; k <= M; k++) {
        for (int i = 0; i < n; i++) {
            if (d[i][k] == 0) {
                continue;
            }
            for (int j = i + 1; j < n; j++) {
                if (d[j][k] == 0) {
                    continue;
                }
                cnt[i][j] += 1ll * d[i][k] * d[j][k];
            }
        }
    }
    
    double ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = std::max(ans, 1.0 * cnt[i][j] / (1ll * d[i][0] * d[j][0]));
        }
    }
    std::cout << std::fixed << std::setprecision(9) << ans << '\n';
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
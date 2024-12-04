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
constexpr int N = 2e5, M = 1e6, SM = 1e3, Inf = 1e9;

void solve()
{
    std::vector<int> prime;
    std::vector vis(SM + 1, false);
    for (int i = 2; i <= SM; i++) {
        if (not vis[i]) {
            prime.push_back(i);
        }
        for (auto &p : prime) {
            if (p * i > SM) {
                break;
            }
            vis[p * i] = true;
            if (i % p == 0) {
                break;
            }
        }
    }

    int n = 0;
    std::cin >> n;
    std::vector a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::vector dp(n + 1, 0ll), cnt(M + 1, 0ll);
    dp[n] = 1;
    for (int i = n; i >= 1; i--) {
        // 分解质因数
        std::vector<int> p;
        for (int j = 0; prime[j] * prime[j] <= a[i]; j++) {
            if (a[i] % prime[j] == 0) {
                p.push_back(prime[j]);
                while (a[i] % prime[j] == 0) {
                    a[i] /= prime[j];
                }
            }
        }
        if (a[i] != 1) {
            p.push_back(a[i]);
        }

        // 容斥
        for (auto s = 1; s < (1 << p.size()); s++) {
            bool flag = false;
            int res = 1;
            for (int j = 0; j < p.size(); j++) {
                if (s >> j & 1) {
                    flag = !flag;
                    res *= p[j];
                }
            }
            if (flag) {
                (dp[i] += cnt[res]) %= Mod;
            }
            else {
                (dp[i] += Mod - cnt[res]) %= Mod;
            }
        }
        for (auto s = 1; s < (1 << p.size()); s++) {
            int res = 1;
            for (int j = 0; j < p.size(); j++) {
                if (s >> j & 1) {
                    res *= p[j];
                }
            }
            (cnt[res] += dp[i]) %= Mod;
        }
    }
    std::cout << dp[1] << '\n';
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
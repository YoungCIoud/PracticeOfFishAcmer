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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e6, K = 1e6, Inf = 1e9;
i64 f[N + 5][2], pre[N + 5];
i64 pw[N + 5], ipw[N + 5];

i64 qpow(i64 a, i64 p) {
    i64 res = 1;
    while (p) {
        if (p & 1) {
            (res *= a) %= Mod;
        }

        p>>= 1;
        (a *= a) %= Mod; 
    }
    return res;
}
i64 inv(i64 a) {
    return qpow(a, Mod - 2);
}

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;

    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        pre[i] = (pre[i - 1] + f[i - 1][0] * ipw[i - 1]) % Mod;
        f[i][0] = (f[i - 1][0] + f[i - 1][1]) * 21ll % Mod;
        f[i][1] = pw[i] * (pre[i] - pre[std::max(0, i - k)] + Mod) % Mod;
    }

    int ans = f[n][0] + f[n][1];
    if (ans >= Mod) {
        ans -= Mod;
    }
    std::cout << ans << '\n';
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;

    pw[0] = 1;
    for (int i = 1; i <= N; i++) {
        pw[i] = pw[i - 1] * 5ll % Mod;
    }
    ipw[N] = inv(pw[N]);
    for (int i = N; i >= 1; i--) {
        ipw[i - 1] = ipw[i] * 5 % Mod;
    }
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
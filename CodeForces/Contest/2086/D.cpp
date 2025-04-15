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
constexpr int N = 5e5, M = 1e5, Inf = 1e9;

i64 qpow(i64 a, i64 p) {
    i64 res = 1;
    while (p) {
        if (p & 1) {
            (res *= a) %= Mod;
        }

        p >>= 1;
        (a *= a) %= Mod;
    }
    return res;
}
i64 inv(i64 a) {
    return qpow(a, Mod - 2);
}

i64 p[N + 5], ip[N + 5];

void solve()
{
    int n = 26;
    std::vector a(n, 0ll);
    
    i64 ans = 1;
    int sum = 0;
    for (auto &i : a) {
        std::cin >> i;
        sum += i;
        if (i != 0) {
            (ans *= ip[i]) %= Mod;
        }
    }

    int eve = sum >> 1, obb = sum + 1 >> 1;
    (ans *= p[eve] * p[obb] % Mod) %= Mod;
    std::vector cnt(eve + 1, 0ll);
    cnt[0] = 1;
    for (int i = 0; i < 26; i++) {
        if (a[i] == 0) {
            continue;
        }

        for (int j = eve; j >= a[i]; j--) {
            cnt[j] += cnt[j - a[i]];
        }
    }

    (ans *= cnt[eve]) %= Mod;
    std::cout << ans << '\n';
    return;
}

int main()
{
    p[0] = 1;
    for (int i = 1; i <= N; i++) {
        p[i] = p[i - 1] * i % Mod;
    }
    ip[N] = inv(p[N]);
    for (int i = N; i >= 1; i--) {
        ip[i - 1] = ip[i] * i % Mod;
    }

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
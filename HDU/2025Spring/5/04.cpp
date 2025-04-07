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

std::vector<i64> base(int mx, int m) {
    std::vector f(2, std::vector(m, 0ll));
    f[0][0] = 1;
    for (int i = 1, u = 1; i <= mx; i++, u ^= 1) {
        for (int j = 0; j < m; j++) {
            f[u][(j + i) % m] = (f[u ^ 1][j] + f[u ^ 1][(j + i) % m]) % Mod;
        }
    }
    return f[mx & 1];
}

i64 solve()
{
    i64 n = 0, m = 0;
    std::cin >> n >> m;
    std::vector res(2, std::vector(m, 0ll));
    res[0] = base(n % m, m);
    if (n < m) {
        return res[0][0] - 1;
    }

    n /= m;
    int len = std::log2(n);
    std::vector f(len + 1, std::vector(m, 0ll));
    f[0] = base(m, m);
    for (int l = 1; l <= len; l++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                (f[l][(i + j) % m] += f[l - 1][i] * f[l - 1][j] % Mod) %= Mod;
            }
        }
    }

    int p = 0;
    for (int l = len; ~l && n; l--) {
        if ((1ll << l) > n) {
            continue;
        }

        n -= (1ll << l); 
        for (int i = 0; i < m; i++) {
            res[p ^ 1][i] = 0;
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                (res[p ^ 1][(i + j) % m] += res[p][i] * f[l][j] % Mod) %= Mod;
            }
        }
        p ^= 1;
    }
    return (res[p][0] - 1 + Mod) % Mod;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        std::cout << solve() << '\n';
    }

    sp();

    return 0;
}
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
constexpr int N = 3e3, M = 1e9, Inf = 1e9, L = 12;
i64 C[N + 5][N + 5];

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Mod;
        }
    }

    std::vector st(n, std::vector(L, std::array<i64, 2>{ 0, 0 }));
    for (int i = 0; i < n; i++) {
        std::cin >> st[i][0][0];
        st[i][0][1] = st[i][0][0];
    }

    for (int l = 1; l < L; l++) {
        for (int i = 0; i + (1 << l) <= n; i++) {
            st[i][l][0] = std::max(st[i][l - 1][0], st[i + (1 << l - 1)][l - 1][0]);
            st[i][l][1] = std::min(st[i][l - 1][1], st[i + (1 << l - 1)][l - 1][1]);
        }
    }
    // 左闭右开
    auto quiry = [&](int l, int r) -> i64 {
        int len = log2(r - l);
        int m = r - (1 << len);
        return std::max(st[l][len][0], st[m][len][0]) * std::min(st[l][len][1], st[m][len][1]) % Mod;
    };

    i64 ans = 0;
    if (k == 1) {
        ans = quiry(0, n);
    }
    else if (k == 2) {
        for (int i = 1; i < n; i++) {
            (ans += (quiry(0, i) + quiry(i, n)) % Mod) %= Mod;
        }
    }
    else {
        for (int len = 1; len + k - 1<= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int d = (i == 0 || i + len == n) ? 1 : 2;
                (ans += quiry(i, i + len) * C[n - len - d][k - 1 - d] % Mod) %= Mod;
            }
        }
    }
    std::cout << ans << '\n';
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
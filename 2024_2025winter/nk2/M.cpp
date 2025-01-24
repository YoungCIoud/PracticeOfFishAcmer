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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector g(3, std::string{});
    std::vector cnt(4, std::vector(10, 0ll));
    for (auto &s : g) {
        std::cin >> s;
        for (int i = 0; i < n; i++) {
            if (s[i] != '?') {
                int d = (cnt[i % 3][s[i] - '0'] == 0) ? 1 : 0;
                cnt[i % 3][0] += d;
                cnt[3][s[i] - '0'] += d;
                cnt[i % 3][s[i] - '0'] = 1;
            }
        }
    }
    
    // 有解判断
    bool ok = true;
    if (cnt[0][0] > 3 || cnt[1][0] > 3 || cnt[2][0] > 3) {
        ok = false;
    }
    for (int i = 1; i <= 9 && ok; i++) {
        if (cnt[3][i] > 1) {
            ok = false;
        }
    }
    std::vector nuknow(n, 0);
    for (int j = 0; j < n && ok; j++) {
        for (int i = 0; i < 3 && ok; i++) {
            if (g[i][j] == '?') {
                nuknow[j]++;
                continue;
            }
            for (int k = i + 1; k < 3 && ok; k++) {
                if (g[i][j] == g[k][j]) {
                    ok = false;
                }
            }
        }
    }

    std::vector fac(10, 1);
    for (int i = 1; i <= 9; i++) {
        fac[i] = fac[i - 1] * i;
    }
    i64 ans = 0;
    if (ok) {
        ans = 1ll * fac[9 - (cnt[0][0] + cnt[1][0] + cnt[2][0])] / (fac[3 - cnt[0][0]] * fac[3 - cnt[1][0]] * fac[3 - cnt[2][0]]);
        for (int j = 0; j < n; j++) {
            (ans *= 1ll * fac[nuknow[j]]) %= Mod;
        }
    }

    std::cout << ans << '\n';
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


/*
4
6
1???56
456789
7891??
3
???
???
?11
3
123
456
789
3
723
18?
?9?

2
0
1
6
*/
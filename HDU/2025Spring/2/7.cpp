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
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 100, K = 20 * 20 * 20;

int f[N + 5][N + 5][K + 5];
int trans[128][K + 5];

int hash(int k, int sum, int mul, int cur) {
    return (sum * k + mul) * k + cur;
}

void solve() {
    int n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int s = 0; s < k * k * k; s++) {
                f[i][j][k] = 0;
            }
        }
    }

    for (int sum = 0; sum < k; sum++) {
        for (int mul = 0; mul < k; mul++) {
            for (int cur = 0; cur < k; cur++) {
                for (char d = '0'; d <= '9'; d++) {
                    trans[d][hash(k, sum, mul, cur)] = hash(k, sum, mul, (cur * 10 + d - '0') % k);
                }
                trans['+'][hash(k, sum, mul, cur)] = hash(k, (sum + mul * cur) % k, 1, 0);
                trans['-'][hash(k, sum, mul, cur)] = hash(k, (sum + mul * cur) % k, k - 1, 0);
                trans['*'][hash(k, sum, mul, cur)] = hash(k, sum, (mul * cur) % k, 0);
            }
        }
    }

    std::vector g(n, std::string{});
    for (int i = 0; i < n; i++) {
        std::cin >> g[i];
        g[i].push_back('+');
    }
    f[0][0][hash(k, 0, 1, (g[0][0] - '0') % k)] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = g[i][j];
            for (int s = 0; s < k * k * k; s++) {
                if (f[i][j][s] == 0) {
                    continue;
                }
                if (i + 1 < n && (std::isdigit(c) || std::isdigit(g[i + 1][j]))) {
                    (f[i + 1][j][trans[g[i + 1][j]][s]] += f[i][j][s]) %= Mod;
                }
                if (std::isdigit(c) || std::isdigit(g[i][j + 1])) {
                    (f[i][j + 1][trans[g[i][j + 1]][s]] += f[i][j][s]) %= Mod;
                }
            }
        }
    }

    std::cout << f[n - 1][m][hash(k, 0, 1, 0)] << '\n';
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

    return 0;
}

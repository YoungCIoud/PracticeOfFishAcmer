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

constexpr i64 Mod = 1e9 + 7, Inf = 1e18;
constexpr int N = 1e6, L = 24;

int main () {
    int n = 0, a = 0, b = 0, c = 0;
    std::cin >> n >> a >> b >> c;
    std::vector card(n, std::array<int, 3>{});
    for (auto &[i, j, k] : card) {
        std::cin >> i >> j >> k;
    }
    std::sort(card.begin(), card.end(),
            [](auto &u, auto &v) -> bool { return u[1] - u[0] < v[1] - v[0]; });

    std::vector f(n + 1, std::vector(c + 1, 0ll));
    for (int i = 1; i <= n; i++) {
        for (int j = std::max(0, i - (a + b)); j <= std::min(c, i); j++) {
            if (j != i) {
                f[i][j] = f[i - 1][j] + card[i - 1][i - j <= a ? 0 : 1];
            }
            if (j != 0) {
                f[i][j] = std::max(f[i][j], f[i - 1][j - 1] + card[i - 1][2]);
            }
        }
    }
    std::cout << f[n][c] << '\n';
    return 0;
}
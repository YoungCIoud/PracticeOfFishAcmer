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
constexpr int B = 30, K = 120;
i64 base[B + 1];
i64 f[B + 1][K + 1][2];

std::array<int, B + 1> trans(i64 n) {
    std::array<int, B + 1> res{};
    for (int i = B; i >= 1; i--) {
        res[i] = 0;
        while (n >= base[i]) {
            n -= base[i];
            res[i]++;
        }
    }
    return res;
}

i64 cnt(std::array<int, B + 1> r, int sum) {
    f[0][0][0] = f[0][0][1] = 1;
    int b = 30;
    while (b && !r[b]) {
        b--;
    }
    
    for (int i = 1; i <= b; i++) {
        for (int s = 0; s <= sum; s++) {
            f[i][s][0] = f[i][s][1] = 0;
            for (int k = 0; k <= std::min(3, s); k++) {
                f[i][s][0] += f[i - 1][s - k][0];
            }

            if (s >= r[i]) {
                f[i][s][1] = f[i - 1][s - r[i]][1];
            }
            for (int k = 0; k <= std::min(s, r[i] - 1); k++) {
                f[i][s][1] += f[i - 1][s - k][0];
            }
        }
        f[i][4][0] += 1;
    }

    return f[b][sum][1];
}

void solve() {
    i64 l = 0, r = 0, k = 0;
    std::cin >> l >> r >> k;
    l--;
    
    std::cout << (k > 120 ? 0ll : cnt(trans(r), k) - cnt(trans(l), k)) << '\n';
    
    return;
}

int main () {
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    for (int i = 1; i <= B; i++) {
        base[i] = base[i - 1] << 2 | 1;
    }

    while (_t--) {
        solve();
    }

    return 0;
}
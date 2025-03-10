#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 2e5, M = 1e5, L = 1e6;

int n, p;
i64 l, r;
std::vector a(N + 5, 0);

int cnt(i64 m) {
    m >>= 1;
    int res = 0;
    if (m <= n) {
        for (int i = 1; i <= m; i++) {
            res ^= a[i];
        }
    }
    else {
        if (m & 1) {
            res = p;
        }
        else {
            res = p ^ cnt(m);
        }
    }
    return res;
}

void solve() {
    std::cin >> n >> l >> r;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    if (n % 2 == 0) {
        n++;
        a[n] = 0;
        for (int i = 1; i + i <= n; i++) {
            a[n] ^= a[i];
        }
    }
    p = 0;
    for (int i = 1; i <= n; i++) {
        p ^= a[i];
    }
    std::cout << (l <= n ? a[l] : cnt(l)) << '\n';
    return;
}

int main () {
    int _t = 1;
    std::cin >> _t;
    while (_t--) {
        solve();
    }


    return 0;
}
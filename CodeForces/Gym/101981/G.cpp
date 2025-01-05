#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 1e9 + 7;
constexpr int N = 2e3;

i64 qpow(i64 a, int p) {
    i64 res = 1;
    for (; p; a = a * a % Mod, p >>= 1) {
        if (p & 1) {
            res = res * a % Mod;
        }
    }
    return res;
}

i64 inv =  qpow(24ll, Mod - 2);
void solve() {
    int n = 0;
    std::cin >> n;
    std::cout << 1ll * n * (n + 1) % Mod * (n + 2) % Mod * (n + 3) % Mod * inv % Mod << '\n';
    return;
}

int main () {
    std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
    int _t = 1;
    std::cin >> _t;
    while (_t--) {
        solve();
    }
    return 0;
}
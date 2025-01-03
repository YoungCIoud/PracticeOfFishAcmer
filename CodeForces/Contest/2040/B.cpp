#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 998244353;
constexpr int N = 1e4, K = 10, L = 100;

void solve() {
    int n = 0;
    std::cin >> n;
    if (n == 1) {
        std::cout << 1 << '\n';
    }
    else {
        int ans = 2;
        while (3 * (1 << ans - 2) - 1 <= n) {
            ans++;
        }
        std::cout << ans - 1 << '\n';
    }
}

int main () {
    int _t = 1;
    std::cin >> _t;
    while (_t--) {
        solve();
    }
    return 0;
}
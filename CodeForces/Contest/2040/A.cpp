#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 998244353;
constexpr int N = 1e4, K = 10, L = 100;

void solve() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector cnt(k, 0);
    std::vector a(n, 0);
    for (int i = 0; i < n; i++) {
         std::cin >> a[i];
         a[i] %= k;
         cnt[a[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (cnt[a[i]] == 1) {
            printf("Yes\n%d\n", i + 1);
            return;
        }
    }
    std::cout << "No\n";
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
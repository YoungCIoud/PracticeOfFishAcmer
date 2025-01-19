#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 1e9 + 7;
constexpr int N = 1e5;

int n;
int a[N + 5];
// cnt bad-subarray with medians x
i64 solve(int x) {
    std::vector b(n + 1, n);
    for (int i = 1; i <= n; i++) {
        b[i] = (a[i] <= x) ? 1 : -1;
        b[i] += b[i - 1];
    }

    std::vector cnt(n * 2 + 1, 0);
    i64 res = 0;
    for (int i = 1, j = 0, sum = n; i <= n; i++) {
        while (a[i] == x && j < i) {
            cnt[b[j++]]++;
        }
        res += cnt[b[i]];
    }
    return res;
}

int main () {
    int _t = 1;
    std::cin >> _t;
    while (_t--) {
        std::cin >> n;
        for (int i = 1; i <= n; i++) {
            std::cin >> a[i];
        }
        i64 ans = 1ll * n * (n + 1) / 2ll;
        for (int x = 1; x <= 10; x++) {
            ans -= solve(x);
        }
        std::cout << ans << '\n';
    }

    return 0;
}
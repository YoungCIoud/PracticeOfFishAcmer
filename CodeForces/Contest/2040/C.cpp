#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 Inf = 1e15, Mod = 998244353;
constexpr int N = 1e4, K = 10, L = 100;

void solve() {
    int n = 0;
    i64 k = 0;
    std::cin >> n >> k;

    bool ok = false;
    if (n > 40 || (1ll << n - 1) >= k) {
        ok = true;
    }
    if (not ok) {
        std::cout << "-1\n";
        return;
    }
    
    k--;
    std::vector vis(n + 1, false);
    std::stack<int> stk;
    for (int i = 60, m = n - 1 - i; ~i; i--, m++) {
        if ((k >> i) & 1) {
            stk.push(m);
            vis[m] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (not vis[i]) {
            std::cout << i << ' ';
        }
    }
    while (not stk.empty()) {
        std::cout << stk.top() << ' ';
        stk.pop();
    }
    std::cout << '\n';
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
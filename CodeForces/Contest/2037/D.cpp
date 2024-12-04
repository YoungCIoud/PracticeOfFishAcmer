#include <bits/stdc++.h>

void solve () {
    int n = 0, m = 0, l = 0;
    std::cin >> n >> m >> l;
    std::vector h(n, std::array<int, 2>{}), up(m, std::array<int, 2>{});
    for (auto &[l, r] : h) {
        std::cin >> l >> r;
    }
    for (auto &[x, val] : up) {
        std::cin >> x >> val;
    }
    int ans = 0;
    long long power = 1;
    std::priority_queue<int> q;
    for (int i = 0, j = 0; i < n; i++) {
        auto &[l, r] = h[i];
        while (j < m && up[j][0] < l) {
            q.push(up[j++][1]);
        }
        while (not q.empty() && power <= r - l + 1) {
            power += q.top();
            q.pop();
            ans++;
        }
        if (power <= r - l + 1) {
            std::cout << -1 << '\n';
            return;
        }
    }
    std::cout << ans << '\n';
    return;
}

int main () {
    int t = 1;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
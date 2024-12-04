#include <bits/stdc++.h>

void solve() {
    int n = 0;
    std::cin >> n;
    std::vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        cnt[a]++;
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += cnt[i] / 2;
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    int t = 1;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
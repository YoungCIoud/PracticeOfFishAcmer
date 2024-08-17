#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1E18;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<i64> dp(k + 1, inf);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int cost[5] {};
        for (int j = 1; j <= 4; j++) {
            std::cin >> cost[j];
        }
        for (int x = std::min(k, 4 * i); x >= 0; x--) {
            for (int j = 1; j <= 4 && x + j <= k; j++) {
                dp[x + j] = std::min(dp[x + j], dp[x] + cost[j]);
            }
        }
    }
    std::cout << dp[k] << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
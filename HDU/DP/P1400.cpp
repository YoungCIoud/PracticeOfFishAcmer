#include <bits/stdc++.h>

using i64 = long long;

// 检查从 v 转移到 u 是否合法
bool chk(int u, int v, int m) {
    if (u & v) {
        return false;
    }

    u |= v;
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (!(u >> i & 1)) {
            cnt++;
        }
        else if (cnt & 1) {
            return false;
        }
    }
    return !(cnt & 1);
    // return cnt & 1 == 0;
}

int main() {
    int n = 0, m = 0;
    while ((std::cin >> n >> m) && n != 0) {
        std::vector dp(n + 1, std::vector(1 << m, 0ll));
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int v = 0; v < (1 << m); v++) {
                for (int u = 0; u < (1 << m); u++) {
                    if (dp[i - 1][u] != 0 && chk(u, v, m)) {
                        dp[i][v] += dp[i - 1][u];
                    }
                }
            }
        }
        std::cout << dp[n][0] << '\n';
    }
    return 0;
}
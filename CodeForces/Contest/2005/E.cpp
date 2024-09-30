#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 300, M = 7;

void solve()
{
    int l = 0, n = 0, m = 0;
    std::cin >> l >> n >> m;

    std::vector<int> a(l + 1, 0);
    std::vector vis(7 + 1, false);
    for (int i = 1; i <= l; i++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= l; i++) {
        if (not vis[a[i]]) {
            vis[a[i]] = true;
        }
        else {
            l--;
        }
    }
    
    std::vector M(n + 1, std::vector(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> M[i][j];
        }
    }
    
    // dp[k][i][j] 在子矩阵(i, j)内找a_k是否赢
    std::vector dp(l + 1, std::vector(n + 1, std::vector(m + 1, false)));
    for (int k = l; k >= 1; k--) {
        for (int i = n; i >= 1; i--) {
            for (int j = m; j >= 1; j--) {
                if (i < n && dp[k][i + 1][j]) {
                    dp[k][i][j] = true;
                }
                else if (j < m && dp[k][i][j + 1]) {
                    dp[k][i][j] = true;
                }
                else if (M[i][j] == a[k] && (i == n || j == m || k == l || !dp[k + 1][i + 1][j + 1])) {
                    dp[k][i][j] = true;
                }
            }
        }
    }

    std::cout << (dp[1][1][1] ? "T" : "N") << '\n';
}

int main()
{
    // IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
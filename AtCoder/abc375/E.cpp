#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;
void solve()
{
    int n = 0;
    std::cin >> n;
    std::array<int, 4> sum{};
    std::vector a(n + 1, 0), b(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i] >> b[i];
        sum[a[i]] += b[i];
    }
    sum[0] = sum[1] + sum[2] + sum[3];
    if (sum[0] % 3) {
        std::cout << -1 << '\n';
        return;
    }

    std::vector dp(2, std::vector(sum[0] + 1, std::vector(sum[0] + 1, Inf)));
    dp[0][sum[1]][sum[2]] = 0;
    for (int i = 1, u = 1, v = 0; i <= n; i++, u ^= 1, v ^= 1) {
        // 在第i个人什么都不做时的转移
        for (int s1 = 0; s1 <= sum[0]; s1++) {
            for (int s2 = 0; s2 <= sum[0]; s2++) {
                dp[u][s1][s2] = dp[v][s1][s2];
            }
        }

        // 第i个人在队列a[i]里
        if (a[i] == 1) {
            for (int s1 = b[i]; s1 <= sum[0]; s1++) {
                for (int s2 = 0; s2 <= sum[0]; s2++) {
                    if (dp[v][s1][s2] == Inf) {
                        continue;
                    }
                    if (s2 + b[i] <= sum[0]) {
                        dp[u][s1 - b[i]][s2 + b[i]] = std::min(dp[u][s1 - b[i]][s2 + b[i]], dp[v][s1][s2] + 1); // 转到队列2
                    }
                    dp[u][s1 - b[i]][s2] = std::min(dp[u][s1 - b[i]][s2], dp[v][s1][s2] + 1); // 转到队列3
                }
            }
        }
        else if (a[i] == 2) {
            for (int s1 = 0; s1 <= sum[0]; s1++) {
                for (int s2 = b[i]; s2 <= sum[0]; s2++) {
                    if (dp[v][s1][s2] == Inf) {
                        continue;
                    }
                    
                    if (s1 + b[i] <= sum[0]) {
                        dp[u][s1 + b[i]][s2 - b[i]] = std::min(dp[u][s1 + b[i]][s2 - b[i]], dp[v][s1][s2] + 1); // 转到队列1
                    }
                    dp[u][s1][s2 - b[i]] = std::min(dp[u][s1][s2 - b[i]], dp[v][s1][s2] + 1); // 转到队列3
                }
            }
        }
        else {
            for (int s1 = 0; s1 <= sum[0]; s1++) {
                for (int s2 = 0; s2 <= sum[0]; s2++) {
                    if (dp[v][s1][s2] == Inf) {
                        continue;
                    }

                    if (s1 + b[i] <= sum[0]) {
                        dp[u][s1 + b[i]][s2] = std::min(dp[u][s1 + b[i]][s2], dp[v][s1][s2] + 1);
                    }
                    if (s2 + b[i] <= sum[0]) {
                        dp[u][s1][s2 + b[i]] = std::min(dp[u][s1][s2 + b[i]], dp[v][s1][s2] + 1);
                    }
                }
            }
        }
    }

    sum[0] /= 3;
    int ans = dp[n & 1][sum[0]][sum[0]];
    std::cout << ((ans == Inf) ? -1 : ans) << '\n';
    return;
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
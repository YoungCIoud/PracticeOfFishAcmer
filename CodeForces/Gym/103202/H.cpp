#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e15;
constexpr int N = 500, M = 1e5;

void solve()
{
    int n = 0, m = 0, R = 0;
    std::cin >> n >> m >> R;
    std::vector card(n + 1, std::array<int, 3>{});
    for (int i = 1; i <= n; i++) {
        auto &[d, k, c] = card[i];
        std::cin >> d >> k >> c;
    }
    // records: rent rec[i][1] bikes in day rec[i][0]
    int cnt = 0;
    std::vector record(m + 1, std::array<int, 2>{});
    for (int i = 1; i <= m; i++) {
        std::cin >> record[i][0] >> record[i][1];
        cnt += record[i][1];
    }
    std::sort(record.begin() + 1, record.end(), [](std::array<int, 2> &a, std::array<int, 2> &b){
        return a[0] < b[0];
    });

    std::vector a(cnt + 1, 0);
    int p = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < record[i][1]; j++) {
            a[p + j] = record[i][0];
        }
        p += record[i][1];
    }

    // for (int i = 1; i <= cnt; i++) {
    //     std::cout << a[i] << " \n"[i == cnt];
    // }
    std::vector f(n + 1, std::vector(cnt + 1, cnt));
    for (int i = 1; i <= n; i++) {
        auto &[d, k, c] = card[i];
        for (int r = cnt, l = cnt; r > 0; r--) {
            while (r - l + 1 <= k && a[r] - a[l] + 1 <= d && l > 0) {
                l--;
            }
            f[i][r] = l;
        }
    }

    std::vector dp(cnt + 1, Inf);
    dp[0] = 0;
    for (int i = 1; i <= cnt; i++) {
        // 该辆车不买卡
        dp[i] = dp[i - 1] + R;
        
        // 买卡
        for (int j = 1; j <= n; j++) {
            dp[i] = std::min(dp[i], dp[f[j][i]] + 1ll * card[j][2]);
        }
    }

    std::cout << dp[cnt] << '\n';

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
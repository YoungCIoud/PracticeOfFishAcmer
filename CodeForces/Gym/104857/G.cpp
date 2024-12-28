#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, M = 1e5, Inf = 0x3f3f3f3f;

void solve()
{
    int n = 0, m = 0, k = 0;
    str s;
    std::cin >> n >> m >> k >> s;
    s = "#" + s;
    vct pre(n + 1, 0);
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + (s[i] == '0');

    // 若再chk里开dp会T
    vct dp(n + 1, vct(k + 1, vct<int>(2, Inf)));
    auto chk = [&](int mid) -> bool
    {
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= k; j++)
                for (int k = 0; k < 2; k++)
                    dp[i][j][k] = Inf;
        dp[0][0][0] = 0;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= k; j++)
            {
                if (s[i] == '0')
                {
                    dp[i][j][0] = std::min(dp[i - 1][j][0], dp[i - 1][j][1]);
                    dp[i][j][1] = std::min(dp[i][j][1], dp[i - 1][j][1] + 1);
                }
                else
                {
                    dp[i][j][0] = dp[i - 1][j][0];
                    dp[i][j][1] = dp[i - 1][j][1];
                }
                
                if (i >= mid && j)
                    dp[i][j][1] = std::min(dp[i][j][1], dp[i - mid][j - 1][0] + pre[i] - pre[i - mid]);
            }
        }

        // for (int i = 1; i <= n; i++)
        //     for (int j = 1; j <= k; j++)
        //         std::cout << "(" << i << "," << j << ")" << "(" << dp[i][j][0] << "," << dp[i][j][1] << ")" << "\t\n"[j == m];

        return std::min(dp[n][k][1], dp[n][k][0]) <= m;
    };
    int l = 1, r = n / k;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (chk(mid)) l = mid + 1;
        else r = mid - 1;
    }
    
    std::cout << (r ? r : -1) << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
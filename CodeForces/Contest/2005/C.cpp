#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 0x3f3f3f3f;
std::string narek = "narek";

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector dp(2, std::vector<int>(5, -Inf));
    dp[0][0] = 0;

    std::vector f(5, std::array<int, 2>());
    for (int t = 1; t <= n; t++) {
        int i = t & 1;
        dp[i] = dp[i ^ 1];

        std::string s;
        std::cin >> s;

        for (int st = 0; st < 5; st++) {
            int cur = st, val = 0;
            for (char &c : s) {
                if (std::find(narek.begin(), narek.end(), c) != narek.end()) {
                    if (c == narek[cur]) {
                        val++;
                        cur = (cur + 1) % 5;
                    }
                    else {
                        val--;
                    }
                }
            }
            
            for (int ed = 0; ed < 5; ed++) {
                dp[i][ed] = std::max(dp[i][ed], dp[i ^ 1][st] + val - (cur - ed + 5) % 5 * 2);
            }
        }
    }
    
    std::cout << dp[n & 1][0] << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
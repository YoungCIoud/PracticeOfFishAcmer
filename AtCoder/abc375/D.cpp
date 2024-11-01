#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    std::vector pos(26, std::vector(0, 0));
    std::string s;
    std::cin >> s;
    for (int i = 0; i < s.length(); i++) {
        pos[s[i] - 'A'].push_back(i);
    }
    i64 ans = 0;
    for (int i = 0; i < 26; i++) {
        int m = pos[i].size();
        if (m > 1) {
            ans -= 1ll * m * (m - 1) / 2ll;
            for (int j = 1; j < m; j++) {
                ans += 1ll * j * pos[i][j];
                ans -= 1ll * (m - j) * pos[i][j - 1];
            }
        }
    }
    std::cout << ans << '\n';
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
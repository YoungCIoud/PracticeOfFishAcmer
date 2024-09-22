#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector pos(n + 1, std::vector(1, 0));
    for (int i = 1; i <= n; i++) {
        int a = 0;
        std::cin >> a;
        pos[a].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        pos[i].push_back(n + 1);
    }
    
    i64 ans = 0;
    const i64 all = (i64)n * (n + 1) / 2ll;
    for (int i = 1; i <= n; i++) {
        i64 com = 0;
        for (int j = 1; j < pos[i].size(); j++) {
            int len = pos[i][j] - pos[i][j - 1] - 1;
            com += (i64)len * (len + 1) / 2ll;
        }
        ans += all - com;
    }
    std::cout << ans << '\n';
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
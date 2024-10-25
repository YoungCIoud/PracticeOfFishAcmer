#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0, c = 0;
    std::cin >> n >> c;
    int cur = -Inf;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        if (a - cur >= c) {
            ans++;
            cur = a;
        }
    }
    std::cout << ans << '\n';
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
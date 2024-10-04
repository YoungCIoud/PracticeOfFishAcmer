#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using u64 = unsigned long long;
using i128 = __int128_t;

constexpr u64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    u64 k = 0;
    std::cin >> k;
    u64 ans = 0;

    u64 l = 1, r = 2e9;
    while (l <= r) {
        u64 m = l + r >> 1;
        if (m * (m - 1) <= k) {
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }
    if (r * (r - 1) == k) {
        ans = r * r - 1;
    }
    else {
        ans = r * r + k - r * (r - 1);
    }
    std::cout << ans << '\n';
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
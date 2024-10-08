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
    std::vector k(n, 0ll);
    i64 sum = 0;
    for (auto &i : k) {
        std::cin >> i;
        sum += i;
    }

    i64 ans = 1e12;
    for (int s = 1; s < (1 << n); s++) {
        i64 cnt = 0;
        for (int i = 0; i < n; i++) {
            if (s >> i & 1) {
                cnt += k[i];
            }
        }
        ans = std::min(ans, std::max(cnt, sum - cnt));
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
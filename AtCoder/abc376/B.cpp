#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    int L = 1, R = 2;
    int ans = 0;
    while (q--) {
        char h = 0;
        int t = 0;
        std::cin >> h >> t;
        if (h == 'L') {
            int mx = std::max(L, t);
            int mn = std::min(L, t);
            if (R < mn || mx < R) {
                ans += mx - mn;
            }
            else {
                ans += (n + mn - mx) % n;
            }

            L = t;
        }
        else {
            int mx = std::max(R, t);
            int mn = std::min(R ,t);
            if (L < mn || mx < L) {
                ans += mx - mn;
            }
            else {
                ans += (n + mn - mx) % n;
            }

            R = t;
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
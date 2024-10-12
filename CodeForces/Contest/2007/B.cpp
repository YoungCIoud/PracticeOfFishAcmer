#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    i64 mx = 0;
    for (int i = 1; i <= n; i++) {
        i64 a;
        std::cin >> a;
        mx = std::max(mx, a);
    }

    while (m--) {
        char ope;
        i64 l = 0, r = 0;
        std::cin >> ope >> l >> r;
        if (l <= mx && mx <= r) {
            mx += ope == '+' ? 1 : -1;
        }
        std::cout << mx << ' ';
    }
    std::cout << '\n';
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
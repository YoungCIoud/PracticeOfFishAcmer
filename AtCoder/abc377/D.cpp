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
    std::vector a(n, std::array<int, 2>{});
    for (auto &[x, y] : a) {
        std::cin >> x >> y;
    }

    std::sort(a.begin(), a.end(), [](std::array<int, 2> u, std::array<int, 2> v){
        if (u[1] == v[1]) {
            return u[0] > v[0];
        }
        else return u[1] < v[1];
    });
    for (int i = 1; i < n; i++) {
        a[i][0] = std::max(a[i - 1][0], a[i][0]);
    }

    i64 ans = 1ll * m * (m + 1) / 2ll;
    for (int i = 1; i <= m; i++) {
        int p = 0;
        if (i >= (*a.begin())[1]) {
            for (int l = 25; l >= 0; l--) {
                if (p + (1 << l) < n && a[p + (1 << l)][1] <= i) {
                    p |= (1 << l);
                }
            }
            ans -= i64(a[p][0]);
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
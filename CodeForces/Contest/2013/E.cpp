#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 0x3f3f3f3f;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector<i64> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        a[0] = std::__gcd(a[0], a[i]);
    }
    for (int i = 1; i <= n; i++) {
        a[i] /= a[0];
    }

    i64 ans = n, cur = 0;
    std::vector<bool> vis(n + 1, false);
    while (cur != 1) {
        int id = 0;
        for (int i = 1; i <= n; i++) {
            if (vis[i]) {
                continue;
            }

            if (id == 0 || std::__gcd(cur, a[id]) > std::__gcd(cur, a[i])) {
                id = i;
            }
        }
        vis[id] = true;
        cur = std::__gcd(cur, a[id]);
        ans += cur - 1;
    }
    std::cout << ans * a[0] << '\n';
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
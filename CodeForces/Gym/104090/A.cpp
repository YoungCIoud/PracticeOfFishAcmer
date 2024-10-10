#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    else {
        i64 g = exgcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}

void solve()
{
    i64 n = 0, m = 0;
    std::cin >> n >> m;
    i64 sum = 0;
    for (int i = 0; i < n; i++) {
        i64 a = 0;
        std::cin >> a;
        sum = (sum + a) % m;
    }

    i64 s = 0, d = 0;
    i64 g1 = exgcd(n, n * (n + 1) / 2, s, d);
    
    i64 k = 0, t = 0;
    i64 g2 = exgcd(g1, m, k, t);

    // std::cout << g2 << '\n';

    i64 cnt = (m - sum + g2 - 1) / g2;
    std::cout << (1ll * sum + 1ll * cnt * g2) % m << '\n';
    std::cout << (1ll * cnt * k % m * s % m + m) % m << ' ';
    std::cout << (1ll * cnt * k % m * d % m + m) % m << '\n';
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
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

using point = std::array<double, 2>;

double dis(point a, point b) {
    return sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]));
}

void solve()
{
    int n = 0;
    std::cin >> n;
    point cur = { 0, 0 };
    double ans = 0;
    for (int i = 0; i < n; i++) {
        double x = 0, y = 0;
        std::cin >> x >> y;
        ans += dis(cur, { x, y });
        cur = { x, y };
    }
    ans += dis(cur, { 0, 0 });
    std::cout << std::fixed << std::setprecision(9) << ans << '\n';
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
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 6, M = 1e5;

typedef std::array<int, 2> node;
double dis(node a, node b) {
    return sqrt(1.0 * (a[0] - b[0]) * (a[0] - b[0]) + 1.0 * (a[1] - b[1]) * (a[1] - b[1]));
}

void solve()
{
    int n = 0, s = 0, t = 0;
    std::cin >> n >> s >> t;
    std::vector line(n, std::array<node, 2>{});
    for (auto &[a, b] : line) {
        std::cin >> a[0] >> a[1] >> b[0] >> b[1];
    }
    std::vector p(n, 0);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }

    double ans = 1e9;
    do
    {
        for (int s = 0; s < (1 << n); s++) {
            double res = dis({ 0, 0 }, line[p[0]][s & 1]);
            for (int i = 1; i < n; i++) {
                int cur = (s >> i) & 1;
                int lst = (s >> i - 1) & 1;
                res += dis(line[p[i]][cur], line[p[i - 1]][lst ^ 1]);
            }
            if (res < ans) {
                ans = res;
                // std::cout << s << ':';
                // for (int i = 0; i < n; i++) {
                //     std::cout << p[i] << " \n"[i == n - 1];
                // }
            }
        }
    } while (std::next_permutation(p.begin(), p.end()));
    
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += dis(line[i][0], line[i][1]);
    }

    printf("%.9lf", ans / (1.0 * s) + sum / (1.0 * t));
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
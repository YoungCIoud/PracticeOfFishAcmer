#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

typedef std::array<int, 2> Node;
Node operator-(const Node &a, const Node &b) {
    return { b[0] - a[0], b[1]-  a[1] };
}
int operator^(const Node &a, const Node &b) {
    return a[0] * b[1] - b[0] * a[1];
}

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector<Node> all(n), p;
    for (auto &[x, y] : all) {
        std::cin >> x >> y;
    }

    p.push_back(all[0]);
    for (int i = 1; i < n; i++) {
        if (p.back()[1] == all[i][1] && all[i][1] == all[(i + 1) % n][1]) {
            continue;
        }

        p.push_back(all[i]);
    }
    if (p[0][1] == p[1][1] && p[0][1] == p.back()[1]) {
        p.erase(p.begin());
    }

    int m = p.size();
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int lst = (i - 1 + m) % m;
        int nxt = (i + 1) % m;
        if (p[i][1] < p[lst][1] && p[i][1] < p[nxt][1]) {
            if (((p[i] - p[lst]) ^ (p[nxt] - p[i])) > 0) {
                ans++;
            }
        }

        if (p[i][1] == p[nxt][1]) {
            if (p[i][0] < p[nxt][0] && p[i][1] < p[lst][1] && p[i][1] < p[(nxt + 1) % m][1]) {
                ans++;
            }
            i++;
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
#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e16;
constexpr int N = 3e5, M = 3e5;
std::pair<int, bool> c[N + 5];
i64 f[N + 5][2];

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> c[i].first;
        c[i].second = false;
    }
    for (int i = 0; i < m; i++) {
        int a = 0;
        std::cin >> a;
        c[a].second = true;
    }
    std::sort(c + 1, c + 1 + n);
    for (int i = 2; i <= n; i++) {
        if (c[i - 1].second) {
            f[i][0] = f[i - 1][1];
            f[i][1] = f[i - 1][0] + pow(c[i].first - c[i - 1].first, 2);
        }
        else {
            f[i][0] = std::min(f[i - 1][0], f[i - 1][1]);
            f[i][1] = std::min(f[i - 1][0] + i64(pow(c[i].first - c[i - 1].first, 2)), i64(f[i - 2][0] + pow(c[i].first - c[i - 2].first, 2)));
        }
    }
    std::cout << std::min(f[n][1], (c[n].second ? Inf : f[n][0])) << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    f[0][0] = f[0][1] = f[1][1] = Inf;

    while (_t--)
    {
        solve();
    }

    return 0;
}
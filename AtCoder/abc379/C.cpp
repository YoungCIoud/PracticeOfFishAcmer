#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    #define cout cout << ">>>\t"
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector a(m + 1, std::array<i64, 2>{});
    for (int i = 1; i <= m; i++) {
        std::cin >> a[i][0];
    }
    for (int i = 1; i <= m; i++) {
        std::cin >> a[i][1];
    }
    std::sort(a.begin() + 1, a.end());
    a.push_back({ n + 1, 0 });
    for (int i = 1; i <= m; i++) {
        a[i][1] += a[i - 1][1];
    }
    i64 ans = 0;
    for (int i = 0; i <= m; i++) {
        if (a[i][1] < a[i + 1][0] - 1) {
            std::cout << -1 << '\n';
            return;
        }
        else {
            i64 d = a[i + 1][0] - a[i][0];
            ans += d * (d - 1) / 2;
            ans += (a[i][1] - (a[i + 1][0] - 1)) * d;
        }
    }
    std::cout << (a[m][1] == n ? ans : -1) << '\n';
    return;
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
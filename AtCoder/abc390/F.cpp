#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 3e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &i : a) {
        std::cin >> i;
    }
    std::vector<int> p(n + 2, -1);
    std::vector<i64> f(n, 0ll);
    f[0] = 1;
    for (int i = 0; i + 1 < n; i++) {
        p[a[i]] = i;
        int cur = a[i + 1];
        f[i + 1] = 1 + f[i] + (i - std::max( {p[cur - 1], p[cur], p[cur + 1] }));

        if (p[cur] < p[cur + 1] && p[cur] < p[cur - 1]) { 
            f[i + 1] -= std::min( {p[cur - 1], p[cur + 1]}) - p[cur];
        }
    }
    std::cout << std::accumulate(f.begin(), f.end(), 0ll) << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
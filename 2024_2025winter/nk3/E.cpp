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
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector<int> a, b;
    for (int i = 0; i < n; i++) {
        int p = 0, v = 0;
        std::cin >> p >> v;
        if (~v) {
            a.push_back(p);
        }
        else {
            b.push_back(p);
        }
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    // 0.5s 的数量
    int l = 0, r = Inf;
    while (l <= r) {
        int m = l + r >> 1;

        int num = 0;
        for (auto &p : a) {
            num += std::upper_bound(b.begin(), b.end(), p + m) - std::upper_bound(b.begin(), b.end(), p);
        }

        if (num >= k) {
            r = m - 1;
        }
        else {
            l = m + 1;
        }
    }
    
    if (r == Inf) {
        std::cout << "No\n";
    }
    else {
        std::cout << "Yes\n";
        double ans = l;
        ans /= 2.0;
        std::cout << std::fixed << std::setprecision(6) << ans << '\n';
    }
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
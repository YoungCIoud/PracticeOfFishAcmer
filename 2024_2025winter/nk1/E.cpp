// 操作成双生数组的最少次数
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

constexpr i64 Mod = 998244353, Inf = 1e15;
constexpr int N = 1e5, M = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
    }
    std::sort(a.begin(), a.end());
    
    int m = n / 2;
    int mid1 = a[m - 1 >> 1] + a[m >> 1] >> 1;
    int mid2 = a[m + n - 1 >> 1] + a[m + n >> 1] >> 1;
    i64 ans = Inf;
    auto cnt = [&](int l, int r, int mid) -> i64 {
        i64 res = 0;
        for (int i = l; i < r; i++) {
            res += abs(mid - a[i]);
        }
        return res;
    };
    for (int i = -2; i <= 2; i++) {
        i64 res = cnt(0, m, mid1 + i);
        for (int j = -2; j <= 2; j++) {
            if (mid1 + i != mid2 + j) {
                ans = std::min(ans, res + cnt(m, n, mid2 + j));
            }
        }
    }
    std::cout << ans << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
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

// 0 首项
// 1 公差
// 2 项数
using seq = std::array<int, 3>;

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;

    std::vector<seq> s;

    int mx = 0;
    for (int i = 1; i <= n; i++) {
        int f = n / i, j = n / f;
        mx = std::max(mx, n % i);
        s.push_back({ n % i, -f, j - i + 1 });
        i = j;
    }

    // for (auto &[x, y, z] : s) {
    //     std::cout << x << ' ' << y << ' ' << z << '\n';
    // }

    // 二分求一个数 x 使得大于等于 x 的数都可以选而 x - 1 只能尽可能多的选
    int l = 0, r = mx;
    while (l <= r) {
        int mid = l + r >> 1;

        int cnt = 0;
        for (auto &[a, d, m] : s) {
            if (mid <= a) {
                int num = std::min(m, (mid - a) / d + 1);
                cnt += num;
            }
        }

        if (cnt > k) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }

    i64 ans = 0;
    for (auto &[a, d, m] : s) {
        if (l <= a) {
            int num = std::min(m, (l - a) / d + 1);
            k -= num;
            int b = a + d * (num - 1);
            ans += 1ll * (a + b) * num / 2;
        }
    }
    ans += 1ll * k * r;
    std::cout << ans << '\n';

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
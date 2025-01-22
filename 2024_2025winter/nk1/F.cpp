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
constexpr int N = 1e5, M = 1e9, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    a.push_back(-1);

    // 需要保证 l 到 r 之间有且只有两个数。
    std::array<int, 2> num = { -1, -1 };
    auto cnt = [&](int l, int r) -> i64 {
        int len = r - l + 1, pre = len;
        std::vector tot(len * 2 + 1, 0);
        i64 res = 0;
        for (int i = 0; i < len; i++) {
            tot[pre]++;
            pre += (a[l + i] == num[0] ? 1 : -1);
            res += tot[pre];
        }
        return res;
    };

    int l = 0, r = 0;
    num[0] = a[l];
    while (a[r] == num[0]) {
        r++;
    }
    if (r != n) {
        num[1] = a[r];
        while (a[r + 1] == num[0] || a[r + 1] == num[1]) {
            r++;
        }
    }
    i64 ans = 0;
    if (~num[1]) {
        while (true) {
            ans += cnt(l, r);
            l = r++;
            if (a[r] == -1) {
                break;
            }
            num = { a[l], a[r] };

            while (a[l - 1] == num[0]) {
                l--;
            }
            while (a[r + 1] == num[0] || a[r + 1] == num[1]) {
                r++;
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

/*
3
3
1 2 1
4
6 6 6 6
6
1 1 4 4 1 4

2
0
6
*/
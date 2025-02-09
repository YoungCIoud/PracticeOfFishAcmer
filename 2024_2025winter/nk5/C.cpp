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

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    i64 n = 0, x = 0, y = 0;
    std::cin >> n >> x >> y;
    std::string a, b, c;
    std::cin >> a >> b >> c;
    std::vector cnt(4, 0ll);
    for (int i = 0; i < n; i++) {
        if (c[i] == '0') {
            if (a[i] == '0' && b[i] == '1') {
                cnt[1]++;
            }
            else if (a[i] == '1' && b[i] == '0') {
                cnt[2]++;
            }
        }
        else {
            if (a[i] == '0' && b[i] == '0') {
                cnt[0]++;
            }
            else if (a[i] == '1' && b[i] == '1') {
                cnt[3]++;
            }
        }
    }

    i64 sum = cnt[0] + cnt[1] + cnt[2] + cnt[3];
    if (x * 2 <= y) {
        std::cout << x * sum << '\n';
    }
    else {
        std::sort(cnt.begin(), cnt.end());
        if (cnt[3] * 2 >= sum) {
            i64 num = sum - cnt[3];
            std::cout << y * num + x * (cnt[3] - num) << '\n';
        }
        else {
            std::cout << y * (sum / 2) + x * (sum % 2) << '\n';
        }
    }

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
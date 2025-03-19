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
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr int N = 2e5, MAX = 1e9; 
i64 a[N + 5], pre[N + 5], suf[N + 5];

void solve() {
    int n = 0;
    std::cin >> n;
    int m = 0;
    for (int i = 0; i < n; i++) {
        int x = 0;
        std::cin >> x;
        if (a[m] * x <= 0) {
            a[++m] = 0;
        }
        a[m] += x;
    }
    pre[0] = suf[m + 1] = 0;
    for (int i = 1; i <= m; i++) {
        pre[i] = pre[i - 1];
        if (a[i] > 0) {
            pre[i] += a[i];
        }
    }
    for (int i = m; i >= 1; i--) {
        suf[i] = suf[i + 1];
        if (a[i] < 0) {
            suf[i] += a[i];
        }
    }
    
    i64 ans = 0;
    for (int i = 1; i <= m; i++) {
        ans = std::max(ans, pre[i] - suf[i]);
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
    return 0;
}

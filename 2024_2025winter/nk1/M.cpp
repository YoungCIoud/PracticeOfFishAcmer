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
constexpr int N = 1e5, M = 1e5, Inf = 1e9 + 10;
int n;
int a[N + 5];
int mxp[N + 5], mnp[N + 5]; // 前后缀最小值
int mxs[N + 5], mns[N + 5]; // 前后缀最大值

void solve()
{
    std::cin >> n;
    mnp[0] = mns[n + 1] = Inf;

    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        mxp[i] = std::max(mxp[i - 1], a[i]);
        mnp[i] = std::min(mnp[i - 1], a[i]);
    }
    for (int i = n; i >= 1; i--) {
        mxs[i] = std::max(mxs[i + 1], a[i]);
        mns[i] = std::min(mns[i + 1], a[i]);
    }
    a[0] = a[n + 1] = Inf;

    int ans = Inf;
    if (n == 1 || mxs[1] == mns[1]) {
        ans = 0;
    }
    else {
        int l = 1;
        while (mns[l] != a[l]) l++;
        int r = l;
        ans = std::max(mxs[1], a[l] * 2) - std::min({ mnp[l - 1], mns[r + 1], 2 * a[l] });

        int mx = 0, tar = std::min(mnp[l - 1], mns[r + 1]);
        while (r <= n || l >= 1) {
            while (l >= 1 && mnp[l - 1] == tar) {
                mx = std::max(mx, a[l]);
                l--;
            }
            while (r <= n && mns[r + 1] == tar) {
                mx = std::max(mx, a[r]);
                r++;
            }
            mx = std::max({ mx, a[l], a[r] });
            l = std::max(l, 1) - 1;
            r = std::min(r, n) + 1;
            ans = std::min(ans, std::max({ mx * 2, mxp[l], mxs[r]}) - std::min({ mns[1] * 2, mnp[l], mns[r] }));
        }
    }
    std::cout << ans << '\n';
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
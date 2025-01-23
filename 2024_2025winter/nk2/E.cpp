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
constexpr int N = 2e5, M = 1e5, Inf = 1e9, L = 20;

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::vector a(n + 1, 0ll), pre(n + 1, 0ll);
    std::vector st(n + 1, std::vector(L, 0ll));
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        st[i][0] = a[i] - pre[i - 1];
        pre[i] = pre[i - 1] + a[i];
    }
    
    for (int l = 1; l < L; l++) {
        for (int i = 1; i + (1 << l) - 1 <= n; i++) {
            st[i][l] = std::max(st[i + (1 << l - 1)][l - 1], st[i][l - 1]);
        }
    }
    auto quiry = [&](int l, int r) -> i64 {
        int len = log2(r - l + 1);
        return std::max(st[l][len], st[r - (1 << len) + 1][len]);
    };

    while (q--) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        i64 ans = 0;
        if (l != r) {
            i64 mx = quiry(l + 1, r);
            mx += pre[l - 1];
            ans = std::max(ans, mx);
        }
        std::cout << ans << '\n';
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
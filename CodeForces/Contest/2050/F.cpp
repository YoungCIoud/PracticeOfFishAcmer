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
constexpr int N = 2e5, M = 1e5, Inf = 1e9, L = 18;

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::vector a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::vector st(n, std::vector(L + 1, 0));
    for (int i = 1; i < n; i++) {
        st[i][0] = abs(a[i] - a[i + 1]);
    }

    for (int l = 1; l <= L; l++) {
        for (int i = 1; i + (1 << l) <= n; i++) {
            st[i][l] = std::__gcd(st[i][l - 1], st[i + (1 << l - 1)][l - 1]);
        }
    }

    while (q--) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        if (l == r) {
            std::cout << 0 << '\n';
        }
        else {
            int len = log2(r - l);
            std::cout << std::__gcd(st[l][len], st[r - (1 << len)][len]) << ' ';
        }
    }
    std::cout << '\n';
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
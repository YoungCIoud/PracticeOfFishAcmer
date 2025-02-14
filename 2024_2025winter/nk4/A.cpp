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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 2e5, M = 1e9, Inf = 1e9;

i64 inv(i64 a, i64 p = Mod - 2) {
    i64 res = 1;
    for (p; p; p >>= 1, a = a * a % Mod) {
        if (p & 1) {
            res = res * a % Mod;
        }
    }
    return res;
}

i64 cnt1(int l1, int r1, int l2, int r2) {
    // std::cout << l1 << ' ' << r1 << '\t' << l2 << ' ' << r2 << '\n';
    if (r1 < l1 || r2 < l2) {
        return 0;
    }
    return 1ll * abs(l2 + r2 - l1 - r1) * (r1 - l1 + 1) % Mod * (r2 - l2 + 1) % Mod * inv(2) % Mod;
}

i64 cnt2(int l, int r) {
    // std::cout << l << ' ' << r << '\n';
    if (r < l) {
        return 0;
    }
    int n = r - l + 1;
    return 1ll * n * (n - 1) % Mod * (n + 1) % Mod * inv(3) % Mod;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    int l1 = 0, r1 = 0;
    std::cin >> l1 >> r1;
    i64 ans = 0;
    for (int i = 0, l2 = 0, r2 = 0; i < n - 1; i++, l1 = l2, r1 = r2) {
        std::cin >> l2 >> r2;
        int l3 = std::max(l1, l2);
        int r3 = std::min(r1, r2);
        
        i64 son = 0;
        if (l3 > r3) {
            son = cnt1(l1, r1, l2, r2);
        }
        else {
            son = cnt1(std::min(l1, l2), l3 - 1, l3, l1 < l2 ? r2 : r1);
            son += cnt1(l3, r3, r3 + 1, std::max(r1, r2)) + cnt2(l3, r3);
            son %= Mod;
        }
        (ans += son * inv(1ll * (r1 - l1 + 1) * (r2 - l2 + 1) % Mod)) %= Mod;
    }
    std::cout << ans << '\n';
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
2
3
1 2
1 2
1 3
4
4 8
2 3
4 10
4 7
*/
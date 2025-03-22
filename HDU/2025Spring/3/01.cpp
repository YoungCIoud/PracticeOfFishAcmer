// Lucas 定理
#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;
int a[N + 5];

int cnt(int L, int x) {
    // 不大于 L 的最大的满足 x 的数
    int cur = 0, res = 0;
    for (int i = 30; i >= 0; i--) {
        if (x >> i & 1) {
            res <<= 1;
            if ((cur | (1 << i)) <= L)
            {
                cur |= (1 << i);
                res |= 1;
            }
        }
    }
    
    return res + 1;
}

void solve()
{
    int n = 0;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    i64 ans = 1ll;
    for (int i = 0, L = 0; i < n; i++) {
        std::cin >> L;
        (ans *= cnt(L, a[i])) %= Mod;
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

    return 0;
}
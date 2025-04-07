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

constexpr i64 Mod = 10007;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

class Lucas {
private:
    int mod;
    std::vector<i64> fa, ifa;
    
    int cnt(int n, int m) {
        if (n < m) {
            return 0;
        }
        return fa[n] * ifa[m] * ifa[n - m] % mod;
    }
public:
    // 根据模数预处理阶乘和阶乘逆元
    Lucas(int m): mod(m) {
        fa.assign(mod, 1ll);
        for (int i = 1; i < mod; i++) {
            fa[i] = fa[i - 1] * i % mod;
        }
        ifa.assign(mod, mod - 1); // 威尔逊定理
        for (int i = mod - 1; i > 0; i--) {
            ifa[i - 1] = ifa[i] * i % mod;
        }
    }

    int C(int n, int m) {
        i64 res = 1;
        while (n || m) {
            (res *= cnt(n % mod, m % mod)) %= mod;
            n /= mod;
            m /= mod;
        }
        return res;
    }
} comb(Mod);

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n, 0);
    for (int cnt = 0, i = 1; i <= n; i += 2) {
        a[cnt++] = i;
    }
    for (int cnt = n, i = 2; i <= n; i += 2) {
        a[--cnt] = i;
    }
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        (ans += 1ll * a[i] * comb.C(n - 1, i)) %= Mod;
    }
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
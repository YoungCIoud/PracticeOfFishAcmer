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

void solve()
{
    int n = 1;
    std::cin >> n;
    std::vector a(n + 1, 0LL);
    std::vector p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        a[i] = 1ll * i * i;
    }

    i64 sum = 0;
    bool ok = true;
    for (int i = 1; i <= n; i++) {
        if (*std::lower_bound(a.begin() + 1, a.end(), sum + p[i]) == sum + p[i]) {
            if (i == n) {
                ok = false;
                break;
            }
            else {
                std::swap(p[i], p[i + 1]);
            }
        }
        sum += p[i];
    }

    if (ok) {
        for (int i = 1; i <= n; i++) {
            std::cout << p[i] << ' ';
        }
        std::cout << '\n';
    }
    else {
        std::cout << -1 << '\n';
    }
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
#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    #define cout cout << ">>>\t"
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
    i64 p = 0, a = 0, b = 0;
    i64 q = 0, c = 0, d = 0;
    i64 cur = 0, T = 0;
    std::cin >> p >> a >> b >> q >> c >> d >> cur >> T;
    if (p > cur || 1ll * (a + c + b + d) > T) {
        std::cout << cur << '\n';
        return;
    }
    
    while (T >= a + b + c + d) {
        i64 num = cur / p;  // 一趟能对换多少
        i64 n = (p - cur % p + num * (q - p) - 1) / (num * (q - p)); // 后n趟拉满每趟的增量都保持不变
        if (((a + c) * num + b + d) * n > T) { // 拉满n趟就超时间了
            i64 _n = T / ((a + c) * num + b + d); // 可拉满且不超时的趟数
            cur += num * (q - p) * _n; // 可拉满_n趟
            T -= ((a + c) * num + b + d) * _n;
            if (T >= a + b + c + d) {   // 剩下的一次就能换完
                i64 __n = (T - b - d) / (a + c);
                cur += __n * (q - p);
            }
            break;
        }

        T -= ((a + c) * num + b + d) * n;
        cur += num * (q - p) * n;
    }

    std::cout << cur << '\n';
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    //#define cout cout << ">>>\t"
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
int a[27] = { 1, 2, 2, 3, 3, 4, 4, 5, 5, 1, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 13, 13, 1, 12 };

void solve()
{
    int n = 0;
    std::cin >> n;
    if (n & 1) {
        if (n < 27) {
            std::cout << -1 << '\n';
        }
        else {
            for (int i = 0; i < 27; i++) {
                std::cout << a[i] << ' ';
            }
            n -= 27;
            if (n == 0) {
                std::cout << '\n';
            }
            for (int i = 1; i + i <= n; i++) {
                std::cout << i + 14 << ' ' << i + 14 << " \n"[i + i == n];
            }
        }
    }
    else {
        for (int i = 1; i + i <= n; i++) {
            std::cout << i << ' ' << i << " \n"[i + i == n];
        }
    }
    return;
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
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
    int n = 0, d = 0;
    std::cin >> n >> d;
    std::vector ok(10, false);
    ok[1] = true;
    if (d == 5) {
        ok[5] = true;
    }
    if (n >= 6) {
        ok[3] = ok[7] = ok[9] = true;
    }
    else if (n >= 3) {
        ok[3] = ok[7] = true;
        if (d % 3 == 0) {
            ok[9] = true;
        }
    }
    else {
        if (d % 3 == 0) {
            ok[3] = true;
        }
        if (d == 7) {
            ok[7] = true;
        }
        if (d == 9) {
            ok[9] = true;
        }
    }
    for (int i = 1; i <= 9; i += 2) {
        if (ok[i]) {
            std::cout << i << ' ';
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
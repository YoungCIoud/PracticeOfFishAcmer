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
    int n = 0;
    std::cin >> n;
    int cnt = 0, mx = 0;
    i64 sum = 0;
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        mx = std::max(a, mx);
        sum += a;
        if (a & 1) {
            cnt++;
        }
    }
    if (cnt == 0 || cnt == n) {
        std::cout << mx << '\n';
    }
    else {
        std::cout << sum - (cnt - 1) << '\n';
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
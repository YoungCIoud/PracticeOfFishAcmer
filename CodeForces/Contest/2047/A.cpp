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
constexpr int N = 100, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0, ans = 0, sum = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        sum += a;
        int b = sqrt(sum);
        if (b * b == sum && b & 1) {
            ans++;
        }
    }
    std::cout << ans << '\n';
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
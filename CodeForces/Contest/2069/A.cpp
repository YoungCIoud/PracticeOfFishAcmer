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

bool solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0);
    for (int i = 1; i < n - 1; i++) {
        std::cin >> a[i];
    }
    for (int i = 1; i < n - 1; i++) {
        if (a[i] == 0 && a[i - 1] == 1 && a[i + 1] == 1) {
            return false;
        }
    }
    return true;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        std::cout << (solve() ? "YES" : "NO") << '\n';
    }

    sp();

    return 0;
}
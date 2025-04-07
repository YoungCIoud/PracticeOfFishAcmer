#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), \
                std::cin.tie(0), \
                std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

bool solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
    }
    if (n >= 24) {
        return true;
    }

    std::map<int, bool> vis;
    for (int i = 1; i < (1 << n); i++) {
        int sum = 0, cnt = 0;
        for (int j = 0; j < n; j++) {
            if (i >> j & 1) {
                sum += a[j];
                cnt++;
            }
        }
        sum |= (cnt << n);
        if (vis[sum]) {
            return true;
        }
        vis[sum] = true;
    }
    return false;
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
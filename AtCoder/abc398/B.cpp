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

bool solve()
{
    std::vector cnt(14, 0);
    int c3 = 0, c2 = 0;
    for (int i = 0; i < 7; i++) {
        int a = 0;
        std::cin >> a;
        cnt[a]++;
        if (cnt[a] == 2) {
            c2++;
        }
        if (cnt[a] == 3) {
            c3++;
        }
    }
    return c3 && (c2 > 1);
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        std::cout << (solve() ? "Yes" : "No") << '\n';
    }

    return 0;
}
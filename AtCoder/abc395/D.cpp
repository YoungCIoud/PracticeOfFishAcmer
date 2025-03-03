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
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::vector idx(n + 1, 0), nest(n + 1, 0), p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        idx[i] = nest[i] = p[i] = i;
    }

    while (q--) {
        int t, a, b;
        std::cin >> t;
        if (t == 1) {
            std::cin >> a >> b;
            p[a] = nest[b];
        }
        else if (t == 2) {
            std::cin >> a >> b;
            std::swap(idx[nest[a]], idx[nest[b]]);
            std::swap(nest[a], nest[b]);
        }
        else {
            std::cin >> a;
            std::cout << idx[p[a]] << '\n';
        }
    }
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
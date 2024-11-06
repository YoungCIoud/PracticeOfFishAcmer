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
    int n = 0;
    std::cin >> n;
    std::vector<int> q(n, 0), r(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> q[i] >> r[i];
    }
    int Q = 0;
    std::cin >> Q;
    while (Q--) {
        int id = 0, d = 0;
        std::cin >> id >> d;
        id--;
        std::cout << 1ll * q[id] * ((d - r[id] + q[id] - 1) / q[id]) + r[id] << '\n';
    }
    return;
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
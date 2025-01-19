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
    std::vector d(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        d[u]++, d[v]++;
    }
    std::vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (d[i] == 1) {
            ans.push_back(i);
        }
    }
    if (ans.size() != 2) {
        std::cout << "-1\n";
    }
    else {
        std::cout << ans[0] << ' ' << ans[1] << '\n';
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
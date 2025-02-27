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
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> e;
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        if (u == v) {
            ans++;
        }
        else {
            if (u > v) {
                std::swap(u, v);
            }
            e.push_back({ u, v });
        }
    }
    if (not e.empty()) {
        std::sort(e.begin(), e.end());
    }
    for (int i = 1; i < e.size(); i++) {
        if (e[i] == e[i - 1]) {
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
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
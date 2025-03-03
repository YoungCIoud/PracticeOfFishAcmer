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
constexpr int N = 1e5, M = 1e5, Inf = 2e9;

void solve()
{
    int n = 0, w = 0;
    std::cin >> n >> w;
    std::vector X(w + 1, std::vector<int>{});
    std::vector idx(n, 0);
    for (int i = 0; i < n; i++) {
        int x = 0, y = 0;
        std::cin >> x >> y;
        X[x].push_back(y);
        idx[i] = X[x].size() - 1;
    }
    int mn = n;
    for (int i = 1; i <= w; i++) {
        mn = std::min(mn, int(X[i].size()));
    }

    std::vector lay(mn, 0);
    for (int i = 1; i <= w; i++) {
        for (int j = 0; j < mn; j++) {
            lay[j] = std::max(lay[j], X[i][j]);
        }
    }
    for (int i = 1; i < mn; i++) {
        lay[i] = std::max(lay[i - 1] + 1, lay[i]);
    }

    int q = 0;
    std::cin >> q;
    while (q--) {
        int T = 0, a = 0;
        std::cin >> T >> a;
        a--;
        std::cout << ((idx[a] < mn ? lay[idx[a]] : Inf) > T ? "Yes" : "No") << '\n';
    }
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
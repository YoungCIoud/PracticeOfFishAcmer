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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, M = 2e5, Inf = 1e9;

int a[N + 5];
std::vector<int> g[N + 5], h[N + 5];
i64 cnt[N + 5], pre[N + 5];

void solve()
{
    int n = 0, c = 0;
    std::cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    
    int m = 0;
    std::cin >> m;
    for (int i = 1; i <= c; i++) {
        g[i].clear(), h[i].clear();
        cnt[i] = pre[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        // 1 <= u, v <= c
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        if (u != v) {
            g[v].push_back(u);
        }
    }
    int k = std::sqrt(c);
    for (int i = 1; i <= c; i++) {
        if (g[i].size() > k) {
            for (auto &to : g[i]) {
                h[to].push_back(i);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        i64 cur = (i == 1 ? 1 : 0);
        int col = a[i];
        if (g[col].size() > k) {
            (cur += pre[col]) %= Mod;
        }
        else {
            for (auto &to : g[col]) {
                (cur += cnt[to]) %= Mod;
            }
        }

        if (i == n) {
            std::cout << cur << '\n';
            return;
        }
        (cnt[col] += cur) %= Mod;
        for (auto &to : h[col]) {
            (pre[to] += cur) %= Mod;
        }
    }
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

/*
这段代码解决了一个图问题，在这个图问题中，点 i 与点 j 之间有一条从 i 向 j 的有向边当且仅当 i < j 且 <a[i], a[j]> 是给出的 <u, v> 无序对中的一个，问从 1 到 n有多少条路径，为了优化时间复杂度，采用了根号分治的策略，请你结合问题描述和代码实现，具体分析下一个用例的时间复杂度。
*/
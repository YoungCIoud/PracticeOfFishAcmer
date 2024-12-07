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
constexpr int N = 2e5, M = 1e5, Inf = 1e9;
std::vector<int> g[N + 5];
void init(int n) {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    return;
}

// 0: 当前节点是路径的端点
// 1: 路径包括当前点且当前点不是端点
// 2: 路径不包括当前点
std::array<int, 3> dfs(int cur, int fa) {
    int d = g[cur].size() - (fa != 0); // 儿子数量
    int n0 = d; // 初始化为单独把现在的点去掉
    int n1 = -Inf, n2 = -Inf;
    int mx1 = -1, mx2 = -1;
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        auto r = dfs(to, cur);
        n2 = std::max({ n2, r[0] + 1, r[1] + 1, r[2] });
        mx2 = std::max(mx2, r[0]);
        if (mx2 > mx1) {
            std::swap(mx1, mx2);
        }
    }
    if (~mx2) {
        n1 = std::max(n1, d - 2 + mx1 + mx2);
    }
    return { std::max(n0, d - 1 + mx1), n1, n2 };
}

void solve()
{
    int n = 0;
    std::cin >> n;
    init(n);
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto ans = dfs(1, 0);
    std::cout << *std::max_element(ans.begin(), ans.end()) << '\n';
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
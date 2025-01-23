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
std::pair<int, int> in[N + 5];
int fa[N + 5];

void dfs(int cur) {
    for (auto &to : g[cur]) {
        if (to != fa[cur]) {
            fa[to] = cur;
            dfs(to);
        }
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        in[i] = { 0, i };
    }
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        in[u].first--, in[v].first--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);
    std::sort(in + 1, in + 1 + n);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int u = in[i].second;
        for (int j = i + 1; j <= std::min(i - in[i].first + 1, n); j++) {
            int v = in[j].second;
            int res = in[i].first + in[j].first + 1;
            if (fa[u] == v || fa[v] == u) {
                res++;
            }
            ans = std::min(res, ans);
        }
    }
    std::cout << -ans << '\n';
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
3
2
1 2
4
1 2
2 3
2 4
7
1 2
1 3
2 4
4 5
5 6
5 7

0
2
4
*/
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
constexpr int N = 2e5, M = 2e5;

std::vector<int> g[N + 5];
bool vis[N + 5];

std::array<int, 2> dfs(int cur, int id = 0) {
    vis[cur] = true;
    std::array<int, 2> res = {0, 0};
    for (auto &to : g[cur]) {
        if (not vis[to]) {
            auto [x, y] = dfs(to, id ^ 1);
            res[0] += x;
            res[1] += y;
        }
    }
    res[id] += 1;
    return res;
}

bool solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int oo = 0, eo = 0, iso = 0;
    i64 X = -m;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            continue;
        }
        auto [x, y] = dfs(i);
        X += 1ll * x * y;

        if (((x + y) & 1)) {
            if (y) {
                eo++;
            }
            else {
                iso++;
            }
        }
        else if (x & 1) {
            oo++;
        }
    }

    if ((n & 1) || eo >= 3) {
        return (oo & 1) ^ (X & 1ll);
    }
    else if (eo) {
        return true;
    }
    else {
        return (iso >> 1 & 1) ^ (X & 1ll);
    }
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        std::cout << (solve() ? "Aoki" : "Takahashi") << '\n';
    }

    return 0;
}
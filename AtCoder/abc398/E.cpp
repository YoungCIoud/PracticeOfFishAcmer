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
constexpr int N = 100, M = 1e5, Inf = 1e9;

std::vector<int> g[N + 5], dep[N + 5];
bool tb[N + 5][N + 5];

void dfs(int cur, int fa, int d = 1) {
    dep[d].push_back(cur);
    for (auto &to : g[cur]) {
        if (to != fa) {
            dfs(to, cur, d + 1);
        }
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n -  1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        tb[u][v] = tb[v][u] = true;
    }

    dfs(1, 0);
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n && not dep[j].empty(); j += 2) {
            for (auto &u : dep[i]) {
                for (auto &v : dep[j]) {
                    tb[u][v] = tb[v][u] = !tb[u][v];
                }
            }
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (tb[i][j]) {
                cnt++;
            }
        }
    }

    int x = 1, y = 2;
    if (cnt & 1) {
        std::cout << "First" << std::endl;
        while (tb[x][y] == false) {
            y++;
            if (y > n) {
                x++;
                y = x + 1;
            }
        }
        std::cout << x << ' ' << y << std::endl;
        tb[x][y] = tb[y][x] = false;
    }
    else {
        std::cout << "Second" << std::endl;
    }

    int xx = 0, yy = 0;
    std::cin >> xx >> yy;
    while (xx != -1) {
        tb[xx][yy] = tb[yy][xx] = false;
        while (tb[x][y] == false) {
            y++;
            if (y > n) {
                x++;
                y = x + 1;
            }
        }
        std::cout << x << ' ' << y << std::endl;
        tb[x][y] = tb[y][x] = false;
        std::cin >> xx >> yy;
    }

    return;
}

int main()
{
    // IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
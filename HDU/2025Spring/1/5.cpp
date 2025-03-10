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

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;
int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    // t[i][j] 表示通过 (i ,j) 时的时间, D[i][j] 表示在 (i, j) 调转方向的时间
    std::vector t(n + 1, std::vector(m + 1, 0ll)), D(n + 1, std::vector(m + 1, 0ll));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> t[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> D[i][j];
        }
    }

    std::vector vis(n + 1, std::vector(m + 1, std::array<bool, 4>{ false, false, false, false }));
    // dis[i][j][k] 表示从起点到(i, j)的最短距离，k表示方向
    std::vector dis(n + 1, std::vector(m + 1, std::array<i64, 4>{ Inf, Inf, Inf, Inf }));

    std::priority_queue<std::tuple<i64, int, int, int>> q;
    q.push({ 0, 1, 0, 0});
    while (not q.empty()) {
        auto [d, x, y, k] = q.top();
        q.pop();
        if (vis[x][y][k]) {
            continue;
        }
        d = -d;
        vis[x][y][k] = true;
        dis[x][y][k] = d;

        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx < 1 || xx > n || yy < 1 || yy > m) {
                continue;
            }
            i64 nd = d + (i == k ? 0 : D[x][y]) + t[xx][yy];
            if (not vis[xx][yy][i] && dis[xx][yy][i] > nd) {
                dis[xx][yy][i] = nd;
                q.push({ -nd, xx, yy, i });
            }
        }
    }

    std::cout << std::min(dis[n][m][0] + D[n][m], dis[n][m][1]) << '\n';
}

int main()
{
    // int size(256<<20);  // 256M
    // __asm__ ( "movq %0, %%rsp\n"::"r"((char*)malloc(size)+size));
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
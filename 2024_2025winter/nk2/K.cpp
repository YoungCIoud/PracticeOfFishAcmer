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
constexpr int N = 500, M = 500, Inf = 1e9;
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int vis[500][500], cnt;

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector g(n, std::string{});
    for (auto &s : g) {
        std::cin >> s;
    }
    auto dfs = [&](auto self, int x, int y, int &res) -> void {
        vis[x][y] = cnt;
        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (xx < 0 || xx >= n || yy < 0 || yy >= m || vis[xx][yy] == cnt) {
                continue;
            }
            if (g[xx][yy] == '0') {
                res++;
                vis[xx][yy] = cnt;
            }
            else {
                self(self, xx, yy, res);
            }
        }
    };

    int ans = Inf;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '0' || vis[i][j] != 0) {
                continue;
            }
            int res = 0;
            cnt++;
            dfs(dfs, i, j, res);
            ans = std::min(ans, res);
        }
    }
    std::cout << ans << '\n';
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
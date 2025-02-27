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
constexpr int N = 1e2, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector g(n, std::string{});
    for (auto &s : g) {
        std::cin >> s;
    }
    std::vector dis(n, std::vector(n, -1));
    std::queue<std::array<int, 2>> q;
    for (int i = 0; i < n; i++) {
        dis[i][i] = 0;
        q.push({ i, i });
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && g[i][j] != '-') {
                dis[i][j] = 1;
                q.push({ i, j });
            }
        }
    }

    // 从已有的回文串向两边拓展
    while (not q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dis[i][j] == -1 && g[i][x] == g[y][j] && g[i][x] != '-') {
                    dis[i][j] = dis[x][y] + 2;
                    q.push({ i, j });
                }
            }
        }
    }
    for (auto &v : dis) {
        for (auto &i : v) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
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
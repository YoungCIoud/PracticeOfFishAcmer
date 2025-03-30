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
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int m, x, y;
std::vector<std::string> g(2);
bool vis[2][M];

// 
bool dfs(int dir, int cx, int cy) {
    if (cx == 2 && cy == y) {
        return true;
    }
    if (cx < 0 || cx > 1 || cy < 0 || cy >= m) {
        return false;
    }
    if (vis[cx][cy]) {
        return false;
    }

    vis[cx][cy] = true;
    bool res = false;
    if (g[cx][cy] == 'I') {
        res = dfs(dir, cx + dx[dir], cy + dy[dir]);
    }
    else {
        res = dfs((dir + 1) % 4, cx + dx[(dir + 1) % 4], cy + dy[(dir + 1) % 4]);
        if (not res) {
            res = dfs((dir + 3) % 4, cx + dx[(dir + 3) % 4], cy + dy[(dir + 3) % 4]);
        }
    }
    vis[cx][cy] = false;
    return res;
}

void solve()
{
    std::cin >> m >> x >> y;
    x--, y--;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < m; j++) {
            vis[i][j] = false;
        }
    }
    for (int i = 0; i < 2; i++) {
        std::cin >> g[i];
    }

    std::cout << (dfs(2, 0, x) ? "YES" : "NO") << '\n';
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

/*
3
3 1 3
ILL
LLI
1 1 1
I
I
3 1 3
IIL
LLI
*/
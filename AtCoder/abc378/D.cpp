#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    #define cout cout << ">>>\t"
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 10, M = 10, Inf = 1e9;
std::vector<int> e[N * M];
std::vector<bool> vis(N * M, 0);
int n = 0, m = 0, k = 0;
int ans = 0;

void dfs(int cur, int dp = 0) {
    if (dp == k) {
        ans++;
        return;
    }
    vis[cur] = true;
    for (auto &to : e[cur]) {
        if (vis[to]) {
            continue;
        }
        dfs(to, dp + 1);
    }
    vis[cur] = false;
}

void solve()
{
    std::cin >> n >> m >> k;
    std::vector g(n, std::string{});
    for (auto &s : g) {
        std::cin >> s;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '#') {
                continue;
            }
            int cur = m * i + j;
            if (i - 1 >= 0 && g[i - 1][j] == '.') {
                e[cur].push_back(cur - m);
            }
            if (i + 1 < n && g[i + 1][j] == '.') {
                e[cur].push_back(cur + m);
            }
            if (j - 1 >= 0 && g[i][j - 1] == '.') {
                e[cur].push_back(cur - 1);
            }
            if (j + 1 < m && g[i][j + 1] == '.') {
                e[cur].push_back(cur + 1);
            }
        }
    }
    
    for (int i = 0; i < n * m; i++) {
        dfs(i);
    }
    std::cout << ans << '\n';
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
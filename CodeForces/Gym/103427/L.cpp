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
constexpr int N = 2000, M = 1e5, Inf = 1e9;
i64 f[N + 5];
std::vector<int> g[N * 2 + 5];
// dp[i][j][0/1] : i的子树下，匹配了j对点，且i点有没有被匹配的方案数
i64 dp[N * 2 + 5][N * 2 + 5][2];
int siz[N * 2 + 5]; // siz[i] : i的子树共有多少个节点

void dfs(int cur, int fa = 0) {
    dp[cur][0][0] = 1ll;
    siz[cur] = 1;
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        dfs(to, cur);
        for (int i = siz[cur] / 2; i >= 0; i--) {
            for (int j = siz[to] / 2; j >= 0; j--) {
                if (j > 0) {
                    (dp[cur][i + j][0] += dp[cur][i][0] * (dp[to][j][0] + dp[to][j][1]) % Mod) %= Mod;
                    (dp[cur][i + j][1] += dp[cur][i][1] * (dp[to][j][0] + dp[to][j][1]) % Mod) %= Mod;
                }
                // cur 和 to 之间新建匹配
                (dp[cur][i + j + 1][1] += dp[cur][i][0] * dp[to][j][0] % Mod) %= Mod;
            }
        }
        siz[cur] += siz[to];
    }
    return;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i < 2 * n; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = (f[i - 1] * (2ll * i - 1)) % Mod;
    }

    dfs(1);
    i64 ans = f[n];
    for (int i = 1; i <= n; i++) {
        if (i & 1) {
            (ans -= (dp[1][i][0] + dp[1][i][1]) * f[n - i] % Mod) %= Mod;
        }
        else {
            (ans += (dp[1][i][0] + dp[1][i][1]) * f[n - i] % Mod) %= Mod;
        }
    }
    std::cout << (ans + Mod) % Mod << '\n';
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
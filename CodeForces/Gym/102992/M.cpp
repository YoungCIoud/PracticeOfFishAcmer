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

constexpr i64 Mod = 998244353, Inf = 1e15;
constexpr int N = 2e3, M = 1e5;

std::vector<int> g[N + 5], siz(N + 5);
std::vector<i64> val(N + 5);
i64 dp[N + 5][N + 5][2];
void init(int n = 0) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j][0] = dp[i][j][1] = Inf;
        }
        g[i].clear();
        siz[i] = 1;
    }
}


void dfs0(int cur, int fa = 0) {
    dp[cur][0][0] = val[cur];
    dp[cur][1][1] = 0;
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        dfs0(to, cur);
        dp[cur][0][0] += val[to];
        dp[cur][1][1] += dp[to][0][0];
    }
    dp[cur][0][0] += dp[cur][1][1];
}

void dfs(int cur, int fa = 0) {
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        dfs(to, cur);
        for (int i = siz[cur]; i >= 0; i--) {
            for (int j = siz[to]; j > 0; j--) {
                dp[cur][i + j][0] = std::min(dp[cur][i + j][0], dp[cur][i][0] - dp[to][0][0] - val[to] + std::min(dp[to][j][0] + val[to], dp[to][j][1]));
                if (i > 0) {
                    dp[cur][i + j][1] = std::min(dp[cur][i + j][1], dp[cur][i][1] - dp[to][0][0] + std::min(dp[to][j][0], dp[to][j][1]));
                }
            }
        }
        siz[cur] += siz[to];
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;
    init(n);
    for (int i = 2; i <= n; i++) {
        int a = 0;
        std::cin >> a;
        g[i].push_back(a);
        g[a].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> val[i];
    }

    dfs0(1);
    dfs(1);

    std::cout << dp[1][0][0] << ' ';
    for (int i = 1; i <= n; i++) {
        std::cout << std::min(dp[1][i][0], dp[1][i][1]) << " \n"[i == n];
    }
    return;
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
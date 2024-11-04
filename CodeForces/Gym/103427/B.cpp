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
constexpr int N = 1e5, M = 2e5, Inf = 1e9;
int n, m;
int vis[N * 2 + 5];
std::array<int, 3> a[M + 5];
std::vector<int> g[N * 2 + 5];

void build(int d) {
    for (int i = 1; i <= m; i++) {
        auto &[u, v, w] = a[i];
        if (w >> d & 1) {
            g[u].push_back(v);
            g[v].push_back(u);
            g[u + n].push_back(v + n);
            g[v + n].push_back(u + n);
        }
        else {
            g[u].push_back(v + n);
            g[v].push_back(u + n);
            g[u + n].push_back(v);
            g[v + n].push_back(u);
        }
    }
}

int n1;
int dfs(int cur, int fa = 0, int id = 1) {
    int val = 1;
    vis[cur] = id;
    if (cur <= n && (id & 1)) {
        n1++;
    }
    for (auto &to : g[cur]) {
        if (vis[to]) {
            if ((id ^ vis[to]) & 1) {
                continue;
            }
            else {
                return 0;
            }
        }

        int sum = dfs(to, cur, id + 1);
        if (sum == 0) {
            return 0;
        }
        else {
            val += sum;
        }
    }

    return val;
}

void solve()
{
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < 3; j++) {
            std::cin >> a[i][j];
        }
    }

    i64 ans = 0;
    for (int i = 0; i < 30; i++) {
        for (int j = 1; j <= n + n; j++) {
            vis[j] = 0;
            g[j].clear();
            g[j].push_back(j + (j <= n ? n : -n));
        }
        build(i);

        for (int j = 1; j <= n; j++) {
            if (vis[j] == 0) {
                n1 = 0;
                int tot = dfs(j) / 2;

                debug("n1 : %d, tot : %d\n", n1, tot);
                if (tot == 0) {
                    std::cout << -1 << '\n';
                    return;
                }
                else {
                    ans += 1ll * (1 << i) * std::min(n1, tot - n1);
                }
            }
        }
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
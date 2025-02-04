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

std::string col;
std::vector<int> g[N];
std::map<std::pair<int, int>, int> idx;
std::array<i64, 2> ans[N];

// 以 i 为一个端点另一端是黑（白）路径的数量
// 以 i 为一个端点另一端是黑（白）路径的总长度
std::array<i64, 2> cnt[N], tot[N];
i64 dp[N]; // 结果

// u 是 v 的父节点， 将 v 转移到 u。
void trans(int u, int v) {
    dp[u] += dp[v] + cnt[u][0] * tot[v][1] + cnt[u][1] * tot[v][0];
    dp[u] += cnt[v][0] * (tot[u][1] - cnt[u][1]) + cnt[v][1] * (tot[u][0] - cnt[u][0]);
    tot[u][0] += tot[v][0] + cnt[v][0];
    tot[u][1] += tot[v][1] + cnt[v][1];
    cnt[u][0] += cnt[v][0];
    cnt[u][1] += cnt[v][1];
}
// u 是 v 的父节点， 将 v 变成父亲
void inv(int u, int v, bool W) {
    tot[u][0] -= tot[v][0] + cnt[v][0];
    tot[u][1] -= tot[v][1] + cnt[v][1];
    cnt[u][0] -= cnt[v][0];
    cnt[u][1] -= cnt[v][1];
    dp[u] -= dp[v] + cnt[u][0] * tot[v][1] + cnt[u][1] * tot[v][0];
    dp[u] -= cnt[v][0] * (tot[u][1] - cnt[u][1]) + cnt[v][1] * (tot[u][0] - cnt[u][0]);

    // 写入答案
    if (W) {
        auto pos = idx.find({ u, v });
        if (pos != idx.end()) {
            ans[(*pos).second] = { dp[u], dp[v] };
        }
        else {
            ans[(*idx.find({ v, u })).second] = { dp[v], dp[u] };
        }
    }

    trans(v, u);
}

void dfs1(int cur, int fa) {
    cnt[cur][(col[cur] == 'b' ? 0 : 1)] = 1;
    tot[cur][(col[cur] == 'b' ? 0 : 1)] = 1;

    for (auto &to : g[cur]) {
        if (to != fa) {
            dfs1(to, cur);
            trans(cur, to);
        }
    }
}

void dfs2(int cur, int fa) {
    for (auto &to : g[cur]) {
        if (to != fa) {
            inv(cur, to, true);
            dfs2(to, cur);
            inv(to, cur, false);
        }
    }
}

void solve()
{
    int n = 0;
    std::cin >> n >> col;
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        idx[{ u, v }] = i;
    }

    dfs1(0, 0);
    dfs2(0, 0);

    for (int i = 0; i < n - 1; i++) {
        std::cout << ans[i][0] << ' ' << ans[i][1] << '\n';
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


/*
in:
5
bwbwb
1 2
2 5
4 1
3 1
out:
3 1
6 0
0 4
0 6
*/
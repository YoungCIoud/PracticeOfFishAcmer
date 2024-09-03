#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 2e5, M = 1e9;
struct Node
{
    int idx, las;
    i64 len;

    bool operator<(const Node& a) const
    {
        return len < a.len;
    }
};

int n, st[N + 5][20], cnt_leaf;
bool vis[N + 5];
vct<std::pair<int, i64>> g[N + 5];
i64 dis[N + 5];
std::priority_queue<Node> q;

// 处理出所有点到0点的距离和父节点
void dfs(int cur, int fa, i64 dep = 0)
{
    dis[cur] = dep, st[cur][0] = fa;

    bool is_leaf = true;
    for (auto& [to, l] : g[cur])
        if (to != fa)
        {
            is_leaf = false;
            dfs(to, cur, dep + l);
        }
    
    if(is_leaf)
    {
        cnt_leaf++;
        q.push({ cur, 1, dep });
    }
}

void solve()
{
    std::cin >> n;
    for (int i = 1; i <= n - 1; i++)
    {
        int u = 0, v = 0;
        i64 l = 0;
        std::cin >> u >> v >> l;
        g[u].push_back({ v, l });
        g[v].push_back({ u, l });
    }
    g[0].push_back({ 1, 0ll });

    dfs(0, 0);

    for (int p = 1; p < 20; p++)
        for (int i = 1; i <= n; i++)
            st[i][p] = st[st[i][p - 1]][p - 1];


    i64 ans = 0;
    vis[0] = true;
    while (!q.empty())
    {
        while (vis[q.top().las])
        {
            int idx = q.top().idx, las = idx;
            q.pop();

            for (int i = 19; i >= 0; i--)
                if (!vis[st[las][i]]) las = st[las][i];
            
            q.push({ idx, las, dis[idx] - dis[st[las][0]] });
        }

        auto [idx, las, len] = q.top();
        q.pop();

        while (!vis[idx])
        {
            vis[idx] = true;
            idx = st[idx][0];
        }

        ans += 2ll * len;
        std::cout << ans << ' ';
    }

    for (int k = cnt_leaf + 1; k <= n; k++) std::cout << ans << ' ';
}

int main()
{
    //IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
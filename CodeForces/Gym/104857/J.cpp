#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 3e5, M = 1e6, Inf = (1ll << 31) - 1;
// 固定一条边(x, y)作为最长边
// 然后再(1,x)(y,n)或者(1,y)(x,n)里找次大值
// 所以需要预处理出1到所有点的路径里 使最长边的长度最小的那条路径的长度最大的边
int n = 0, m = 0;

int head[N + 5], nex[M * 2 + 5], to[M * 2 + 5], val[M * 2 + 5];
int tot = 2;
void add(int u, int v, int w)
{
    nex[tot] = head[u], to[tot] = v, val[tot] = w;
    head[u] = tot;
    tot++;
}


void dij(int s, vct<int>& dis)
{
    vct vis(n + 1, false);
    std::priority_queue<std::pair<int, int>> q{};
    q.push({ 0, s });
    dis[s] = 0;
    while (!q.empty())
    {
        auto [d, cur] = q.top();
        q.pop();

        if (vis[cur]) continue;
        d = -d;
        for (int i = head[cur]; i; i = nex[i])
        {
            if (!vis[to[i]] && dis[to[i]] > std::max(dis[cur], val[i]))
            {
                dis[to[i]] = std::max(dis[cur], val[i]);
                q.push({ -dis[to[i]], to[i] });
            }
        }
    }
    return;
}

void solve()
{
    std::cin >> n >> m;
    vct<ary<int, 3>> edge(m);
    for (int i = 0; i < m; i++)
    {
        int u = 0, v = 0, w = 0;
        std::cin >> u >> v >> w;

        edge[i] = { u, v, w };
        add(u, v, w);
        add(v, u, w);
    }

    vct d1(n + 1, Inf), dn(n + 1, Inf);
    dij(1, d1), dij(n, dn);

    int ans = Inf;
    for (auto &[x, y, z] : edge)
    {
        int t = std::min(std::max(d1[x], dn[y]), std::max(d1[y], dn[x]));
        if (t <= z) ans = std::min(ans, z + t);
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

    system("pause");

    return 0;
}
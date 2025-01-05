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

constexpr i64 Mod = 998244353, Inf = 1e9;
namespace Dinic
{
    // 以下数据依据具体要求确定
    constexpr int N = 1000 + 10, M = 250005; // 数据规模
    constexpr int S = N + 1, T = N + 4; // 源点 汇点
    
    // 链式前向星
    struct Edge
    {
        int nex, to;
        i64 f;
    }edge[M * 2 + 5]; // 因为要反向建边所以要开两倍空间
    int head[N + 5];
    int tot = 2;

    int ind[N + 5]; // 弧优化
    // 建边时正向边和反向边挨着建
    void add(int u, int v, i64 w)
    {
        edge[tot] = { head[u], v, w };
        head[u] = tot++;

        edge[tot] = { head[v], u, 0 };
        head[v] = tot++;
    }
    // bfs 建分层图
    // 同时可以根据level来找割边集
    int level[N + 5];
    bool mklv()
    {
        std::queue<int> q;
        memset(level, 0, sizeof level);
        q.push(S);
        level[S] = 1;
        ind[S] = head[S];
        while (not q.empty())
        {
            int cur = q.front();
            q.pop();
            
            for (int e = head[cur]; e; e = edge[e].nex)
            {
                auto& [nex, to, f] = edge[e];
                if (level[to] == 0 and f)
                {
                    level[to] = level[cur] + 1;
                    ind[to] = head[to];
                    q.push(to);
                }
            }
            // return true when reach T
            if (level[T])
                return true;
        }
        // cannot reach T
        return false;
    }

    i64 dfs(int cur, i64 flow)
    {
        if (cur == T)
            return flow;

        i64 sum = 0;
        // 注意弧优化
        for (int e = ind[cur]; e; ind[cur] = e, e = edge[e].nex)
        {
            auto& [nex, to, f] = edge[e];
            if (f <= 0 or level[to] != level[cur] + 1)
                continue;

            // 总共流入了flow, 能够从这条边流出的最大值
            i64 mx = dfs(to, std::min(flow - sum, f));
            f -= mx;
            edge[e ^ 1].f += mx;
            sum += mx;

            if (sum == flow)
                return flow;
        }
        if (sum == 0)
            level[cur] = 0;
        return sum;
    }

    i64 dinic()
    {
        i64 res = 0;
        while (mklv())
            res += dfs(S, Inf);
        return res;
    }
}

void solve()
{
    int n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;
    int s1 = Dinic::S + 1, s2 = s1 + 1;
    Dinic::add(Dinic::S, s1, n);
    Dinic::add(Dinic::S, s2, k);
    for (int i = 1; i <= n; i++) {
        Dinic::add(s1, i, 1);
        Dinic::add(s2, i, 1);
        int t = 0;
        std::cin >> t;
        while (t--) {
            int a = 0;
            std::cin >> a;
            Dinic::add(i, n + a, 1);
        }
    }
    for (int i = n + 1; i <= n + m; i++) {
        Dinic::add(i, Dinic::T, 1);
    }
    std::cout << Dinic::dinic() << '\n';
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
## Dinic
求最大流和最小割
```c++
namespace Dinic
{
    // 以下数据依据具体要求确定
    constexpr int N = 11111, M = 233333; // 数据规模
    constexpr int S = 10100, T = 10101; // 源点 汇点
    
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
```

## 割点 tarjan
```c++
// 时间戳, 最小值, 时间
int dfn[N + 5], low[N + 5], tim;
bool cp[N + 5];
void tarjan(int cur, int fa)
{
    dfn[cur] = low[cur] = ++tim;
    int son = 0;
    for (auto& to : g[cur])
    {
        if (to == fa) continue;

        if (dfn[to] == 0)
        {
            son++;
            tarjan(to, cur);
            low[cur] = std::min(low[cur], low[to]);
            // 如果发现to和cur的祖先不连通
            if (cur != fa && dfn[cur] <= low[to])
                cp[cur] = true;
        }
        else
        {
            // 注意此处和上面比大小的不同
            low[cur] = std::min(low[cur], dfn[to]);
        }
    }
    if (cur == fa && son > 1)
        cp[cur] = true;
}
```
## 割边 tarjan
```c++
// 时间戳, 最小值, 时间
int dfn[N + 5], low[N + 5], tim;
bool ce[N + 5];
int las[N + 5]; // 当ce[i]为真时, (las[i], i)是一条割边
void tarjan(int cur, int fa)
{
    las[cur] = fa;
    dfn[cur] = low[cur] = ++tim;
    for (auto& to : g[cur])
    {
        if (to == fa) continue;

        if (dfn[to] == 0)
        {
            tarjan(to, cur);
            low[cur] = std::min(low[cur], low[to]);
            // 发现儿子和自己都不连通
            // 此时 cur -> to 这一条边是割边
            if (dfn[cur] < low[to])
                ce[to] = true;
        }
        else
        {
            // 注意此处和上面比大小的不同
            low[cur] = std::min(low[cur], dfn[to]);
        }
    }
}
```
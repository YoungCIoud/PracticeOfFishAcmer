#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 26 * 26, M = 1e5;
std::vector<int> g[N];

int dfn[N], low[N], tim;
int stk[N], top, scc[N], cnt;
bool in[N];
void dfs(int cur) {
    dfn[cur] = low[cur] = ++tim;
    stk[top++] = cur;
    in[cur] = true;
    for (int &to : g[cur]) {
        if (dfn[to] == 0) {
            dfs(to);
            low[cur] = std::min(low[cur], low[to]);
        }
        else if (in[to]) {
            low[cur] = std::min(low[cur], low[to]);
        }
    }

    if (low[cur] == dfn[cur]) {
        while (stk[top] != cur) {
            top--;
            scc[stk[top]] = cnt;
            in[stk[top]] = false;
        }
        cnt++;
    }
}

namespace Dinic
{
    // 以下数据依据具体要求确定
    constexpr int N = 26 * 26 * 2, M = 26 * 26 * 26 * 26; // 数据规模
    constexpr int S = N, T = N + 1; // 源点 汇点
    
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
    for (int i = 0; i < N; i++) {
        stk[i] = -1;
    }

    int n = 0;
    std::cin >> n;
    std::vector<std::string> s(n);
    for (auto &i : s) {
        std::cin >> i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i].back() == s[j].front()) {
                g[i].push_back(j);
            }
        }
    }

    // std::vector oc(N, false);
    // for (int i = 0; i < n; i++) {
    //     std::string s;
    //     std::cin >> s;
    //     if (s[0] != s[1]) {
    //         g[s[0] - 'A'].push_back(s[1] - 'A');
    //     }
    //     oc[s[0] - 'A'] = oc[s[1] - 'A'] = true;
    // }

    for (int i = 0; i < n; i++) {
        if (dfn[i] == 0) {
            dfs(i);
        }
    }

    std::vector G(cnt, std::vector(cnt, false));
    for (int cur = 0; cur < n; cur++) {
        for (int &to : g[cur]) {
            if (scc[cur] != scc[to]) {
                G[scc[cur]][scc[to]] = true;
            }
        }
    }
    for (int k = 0; k < cnt; k++) {
        for (int i = 0; i < cnt; i++) {
            for (int j = 0; j < cnt; j++) {
                if (G[i][k] && G[k][j]) {
                    G[i][j] = true;
                }
            }
        }
    }

    for (int i = 0; i < cnt; i++) {
        Dinic::add(Dinic::S, i, 1);
        Dinic::add(i + cnt, Dinic::T, 1);
        for (int j = 0; j < cnt; j++) {
            if (G[i][j]) {
                Dinic::add(i, j + cnt, 1);
            }
        }
    }

    std::cout << cnt - Dinic::dinic() << '\n';
}


int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
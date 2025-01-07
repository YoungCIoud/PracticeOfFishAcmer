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
constexpr int N = 1e3, M = 1e5, Inf = 1e9;

int n = 0, m = 0;
std::vector<int> g[N * 2], in(N * 2);
bool need[N * 2];

int dfn[N * 2], tim, low[N * 2];
int scc[N * 2], sz[N * 2];
int stk[N * 2], top;
int vis[N * 2];

void init() {
    tim = 0, top = -1;
    for (int i = 0; i < n + m; i++) {
        g[i].clear();
        in[i] = 0;
        need[i] = vis[i] = false;
        dfn[i] = low[i] = scc[i] = sz[i] = 0;
    }
}

//// 从cur开始找有没有环
// bool dfs(int cur) {
//     if (vis[cur] == 2) {
//         return false;
//     }
//     vis[cur] = 1;
//     bool res = false;
//     for (auto &to : g[cur]) {
//         if (vis[to] == 2) {
//             continue;
//         }
//         else if (vis[to] == 0) {
//             res |= dfs(to);
//         }
//         else {
//             res = true;
//         }
//     }
//     vis[cur] = 2;
//     return res;
// }

void dfs(int cur) {
    dfn[cur] = low[cur] = ++tim;
    stk[++top] = cur, vis[cur] = true;
    for (auto &to : g[cur]) {
        if (dfn[to] == 0) {
            dfs(to);
            low[cur] = std::min(low[cur], low[to]);
        }
        else if (vis[to]) {
            low[cur] = std::min(low[cur], dfn[to]);
        }
    }
    if (dfn[cur] == low[cur]) {
        do {
            scc[stk[top]] = cur;
            sz[cur]++;
            vis[stk[top]] = false;
        } while (stk[top--] != cur);
    }
}


bool judge() {
    for (int i = 0; i < n + m; i++) {
        if (dfn[i] == 0) {
            dfs(i);
        }
    }

    std::queue<int> q;
    for (int i = 0; i < n + m; i++) {
        if (need[i]) {
            // 在一个环里
            if (sz[scc[i]] != 1) {
                return false;
            }
            q.push(i);
        }
    }
    while (not q.empty()) {
        int cur = q.front();
        q.pop();

        for (auto &to : g[cur]) {
            // 能够到达一个环
            if (sz[scc[to]] != 1) {
                return false;
            }
            if (--in[to] == 0) {
                q.push(to);
            }
        }
    }

    return true;
}

void solve()
{
    std::cin >> n >> m;
    std::vector a(n, std::vector(m, 0));
    std::vector b(n, std::vector(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> b[i][j];
        }
    }
    
    bool ok = true;
    for (int k = 0; k < 30; k++) {
        init();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int x = a[i][j] >> k & 1;
                int y = b[i][j] >> k & 1;
                if (x ^ y) {
                    need[x ? i : j + n] = true;
                }
                if (y) {
                    g[i].push_back(n + j);
                    in[n + j]++;
                }
                else {
                    g[n + j].push_back(i);
                    in[i]++;
                }
            }
        }

        ok = judge();
        if (not ok) {
            break;
        }
    }

    puts(ok ? "Yes" : "No");
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e4, M = 1e5;
std::vector<int> g[N + 5], S[N + 5];

int dfn[N + 5], low[N + 5], tim;
int stk[N + 5], top, cnt, scc[N + 5];
bool vis[N + 5];
void dfs(int cur) {
    dfn[cur] = low[cur] = ++tim;
    stk[top++] = cur;
    vis[cur] = true;
    for (int &to : g[cur]) {
        if (vis[to]) {
            low[cur] = std::min(low[cur], dfn[to]);
        }
        else if (dfn[to] == 0) {
            dfs(to);
            low[cur] = std::min(low[cur], low[to]);
        }
    }

    if (low[cur] == dfn[cur]) {
        cnt++;
        while (stk[top] != cur) {
            top--;
            scc[stk[top]] = cnt;
            S[cnt].push_back(stk[top]);
            vis[stk[top]] = false;
        }
    }
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            dfs(i);
        }
    }

    std::cout << cnt << '\n';
    for (int i = 1; i <= n; i++) {
        if (dfn[i]) {
            std::sort(S[scc[i]].begin(), S[scc[i]].end());
            for (auto s : S[scc[i]]) {
                std::cout << s << ' ';
                dfn[s] = 0;
            }
            std::cout << '\n';
        }
    }
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
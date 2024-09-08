#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7, Inf = 1e18;
constexpr int N = 1e6, M = 1e5;

vct<int> pos[N + 5];
vct<int> g[N * 2 + 5], col(N * 2 + 5);

bool dfs(int cur)
{
    for (auto &to : g[cur])
    {
        if (col[to])
        {
            if (col[to] == col[cur]) return false;
            else continue;
        }
        col[to] = col[cur] == 1 ? 2 : 1;
        if(!dfs(to)) return 0;
    }
    return true;
}

int solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;

    for (int i = 1; i <= m; i++) pos[i].clear();
    for (int i = 1; i <= n + n; i++) g[i].clear(), col[i] = 0;

    for (int i = 1; i <= n; i++)
    {
        str s{};
        std::cin >> s;
        for (int j = 0; j < m; j++)
            if (s[j] == '1')
                pos[j + 1].push_back(i);
        
        g[i].push_back(i + n);
        g[i + n].push_back(i);
    }
    
    if ((m & 1) && pos[m + 1 >> 1].size() > 1) return 0;

    for (int i = 1; i + i <= m; i++)
    {
        if (pos[i].size() + pos[m - i + 1].size() > 2) return 0;
        if (pos[i].size() + pos[m - i + 1].size() < 2) continue;

        if (pos[i].size() == 1)
        {
            int u = pos[i][0], v = pos[m - i + 1][0];
            if (u == v) continue;
            g[u].push_back(v + n);
            g[v].push_back(u + n);
            g[u + n].push_back(v);
            g[v + n].push_back(u);
        }
        else
        {
            int u = 0, v = 0;
            if (pos[i].size()) u = pos[i][0], v = pos[i][1];
            else u = pos[m - i + 1][0], v = pos[m - i + 1][1];
            if (u == v) continue;
            g[u].push_back(v);
            g[v].push_back(u);
            g[u + n].push_back(v + n);
            g[v + n].push_back(u + n);
        }
    }

    int ans = 1;
    for (int i = 1; i <= n + n; i++)
    {
        if (col[i]) continue;
        col[i] = 1;
        if (dfs(i)) ans = 2ll * ans % Mod;
        else ans = 0;
    }
    return ans;
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        std::cout << solve() << '\n';
    }

    system("pause");

    return 0;
}
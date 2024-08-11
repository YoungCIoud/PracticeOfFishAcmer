#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

vct<int> g[N + 5], deep(N + 5);

void dfs(int cur, int fa, int sum)
{
    deep[cur] = sum;
    for (auto& to : g[cur])
        if (to != fa) dfs (to, cur, sum + 1);
}

void solve()
{
    int n, s, r1, r2;
    std::cin >> n >> s >> r1 >> r2;

    for (int i = 1; i <= n; i++) g[i].clear();

    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0, 0);
    int rt = 0;
    for (int i = 1; i <= n; i++)
        if (deep[rt] < deep[i]) rt = i;
    dfs (rt, 0, 0);
    int d = 0;
    for (int i = 1; i <= n; i++)
        d = std::max(d, deep[i]);
    //std::cout << d << ' ';
    if (r2 <= 2 * r1 || d <= 2 * r1) puts("Kangaroo_Splay");
    else puts("General_Kangaroo");
    return;
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
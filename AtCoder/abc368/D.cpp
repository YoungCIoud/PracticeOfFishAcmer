#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 2e5, M = 1e5;

vct<int> g[N + 5];
vct<bool> s(N + 5, false);
vct<int> num(N + 5, 0);
int n = 0, k = 0;

void dfs(int cur, int fa)
{
    for (int &to : g[cur])
    {
        if (to == fa) continue;

        dfs(to, cur);

        num[cur] += num[to];
        if (num[to] != 0 && num[to] != k) s[cur] = 1;
    }
}

void solve()
{
    std::cin >> n >> k;

    for (int i = 0; i < n - 1; i++)
    {
        int u = 0, v = 0;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < k; i++)
    {
        int u = 0;
        std::cin >> u;
        s[u] = true, num[u] = 1;
    }

    dfs(1, 0);

    int ans = 0;
    for (int i = 1; i <= n; i++) ans += s[i] ? 1 : 0;
    std::cout << ans << '\n';
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
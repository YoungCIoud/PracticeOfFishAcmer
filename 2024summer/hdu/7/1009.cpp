#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;

constexpr i64 Mod = 998244353, Inf = 1e9;
constexpr int N = 1e5, M = 1e5;
vct<int> a(N + 5);
vct<ary<int, 2>> g[N + 5];

i64 dfs(int cur, i64 tot)
{
    if (tot >= Inf) return Inf;

    i64 res = 0;
    if (a[cur])
    {
        res = std::min(Inf, tot * a[cur]);
    }
    
    for (auto& [to, num] : g[cur])
    {
        res += dfs(to, tot * num);

        if (res >= Inf)
        {
            res = Inf;
            break;
        }
    }

    return res;
}

void solve()
{
    int n = 0, rt = 0;
    std::cin >> n >> rt;
    for (int i = 1; i <= n; i++)
    {
        a[i] = 0;
        g[i].clear();

        int ope = 0;
        std::cin >> ope;
        if (ope)
        {
            int t = 0;
            std::cin >> t;
            while (t--)
            {
                int u = 0, v = 0;
                std::cin >> u >> v;
                g[i].push_back({ v, u });
            }
        }
        else
        {
            std::cin >> a[i];
        }
    }

    if (a[rt])
    {
        std::cout << a[rt] << '\n';
        return;
    }

    i64 sum = 0, mx = 0;
    for (auto& [to, num] : g[rt])
    {
        i64 res = dfs(to, num);

        if (res == Inf && mx == Inf)
        {
            puts("Impossible");
            return;
        }

        mx = std::max(mx, res);
        sum += res;
    }

    sum -= mx;
    if (sum >= Inf)
    {
        puts("Impossible");
    }
    else
    {
        std::cout << sum << '\n';
    }

    return;
}

int main()
{
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");
    
    return 0;
}
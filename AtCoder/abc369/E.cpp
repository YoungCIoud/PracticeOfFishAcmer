#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e15;
constexpr int N = 400, M = 2e5;

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    vct p(m + 1, ary<int, 2>{ 0, 0 });
    vct t(m + 1, 0);
    vct dis(n + 1, vct(n + 1, Inf));
    for (int i = 1; i <= m; i++)
    {
        std::cin >> p[i][0] >> p[i][1] >> t[i];

        if (t[i] < dis[p[i][0]][p[i][1]])
            dis[p[i][0]][p[i][1]] = dis[p[i][1]][p[i][0]] = t[i];
    }
    
    // Floyd
    for (int i = 1; i <= n; i++) dis[i][i] = 0;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
    
    int q = 0;
    std::cin >> q;
    while (q--)
    {
        int k = 0;
        std::cin >> k;
        vct<int> b(k);
        for (int &i : b) std::cin >> i;
        std::sort(b.begin(), b.end());

        i64 ans = Inf;
        vct s(1, 1);
        auto dfs = [&](auto self, int dep) -> void
        {
            if (dep == k)
            {
                s.push_back(n);

                i64 res = 0;
                for (int i = 0; i <= k; i++)
                    res += dis[s[i * 2]][s[i * 2 + 1]];
                ans = std::min(ans, res);
                
                s.pop_back();
                return;
            }
            else
            {
                for (int i = 0; i < 2; i++)
                {
                    s.push_back(p[b[dep]][i]), s.push_back(p[b[dep]][i ^ 1]);

                    self(self, dep + 1);

                    s.pop_back(), s.pop_back();
                }
            }
        };
        do
        {
            dfs(dfs, 0);
        } while (std::next_permutation(b.begin(), b.end()));
        for (int &i : b) ans += t[i];
        std::cout << ans << '\n';
    }
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
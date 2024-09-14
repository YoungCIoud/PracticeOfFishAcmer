#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, M = 1e5, Inf = 0x3f3f3f3f;

void solve()
{
    int w['Z'] = { 0 };
    w['B'] = 3;
    w['G'] = 2;
    w['R'] = 1;
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::unordered_map<str, vct<int>> pos;
    vct<str> city(n + 1);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> city[i];
        pos[city[i]].push_back(i);
    }

    while (q--)
    {
        int x = 0, y = 0;
        std::cin >> x >> y;
        if (x > y) std::swap(x, y);

        bool same = false;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                same |= (city[x][i] == city[y][j]);
        if(same)
        {
            std::cout << y - x << '\n';
        }
        else
        {
            // 只中转一次
            // 枚举中转城市
            int ans = Inf;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    str mid{};
                    mid.push_back(city[x][i]);
                    mid.push_back(city[y][j]);
                    if (w[mid[0]] < w[mid[1]]) std::swap(mid[0], mid[1]);
                    if (pos[mid].empty()) continue;

                    auto it = std::upper_bound(pos[mid].begin(), pos[mid].end(), x);
                    if (it != pos[mid].end())
                    {
                        if (*it < y) ans = y - x;
                        else ans = std::min(ans, *it - x + *it - y);
                    }
                    if (it != pos[mid].begin())
                    {
                        it--;
                        ans = std::min(ans, x- *it + y - *it);
                    }
                }
            }

            std::cout << (ans == Inf ? -1 : ans) << '\n';
        }
    }
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
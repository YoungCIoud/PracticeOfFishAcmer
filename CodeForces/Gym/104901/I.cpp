#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    vct<int> pos(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        int a = 0;
        std::cin >> a;
        pos[a] = i;
    }

    vct<ary<int, 2>> ans{};
    int r = 0;
    for (int i = 1; i <= n; i++)
    {
        r = std::max(i, r);
        if (pos[i] <= r) continue;

        int mx = 0;
        for (int j = i; pos[j] > r; j++)
            mx = std::max(mx, pos[j]);
        
        r = mx;
        ans.push_back({ i, r });
    }

    std::cout << ans.size() << '\n';
    for (auto [u ,v] : ans)
        std::cout << u << ' ' << v << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
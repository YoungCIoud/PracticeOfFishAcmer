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
    int h = 0, w = 0, n = 0;
    std::cin >> h >> w >> n;
    vct<std::pair<int, int>> a(n);
    for (auto& [i, j] : a) std::cin >> i >> j;
    sort(a.begin(), a.end());
    a.push_back({ h, w });

    vct<int> lis(n + 5, w + 1), pre(n + 5, -1), id(n + 5, -1);
    int mx = 0;
    for (int i = 0; i <= n; i++)
    {
        int it = std::upper_bound(lis.begin(), lis.end(), a[i].second) - lis.begin();
        
        id[it] = i;
        lis[it] = a[i].second;
        pre[i] = it ? id[it - 1] : -1;

        mx = std::max(mx, it);
    }

    std::cout << mx << '\n';

    std::stack<int> stk;
    while (~n)
    {
        stk.push(n);
        n = pre[n];
    }
    int x = 1, y = 1;
    while (!stk.empty())
    {
        auto [xx, yy] = a[stk.top()];
        stk.pop();
        for (x; x < xx; x++) std::cout << 'D';
        for (y; y < yy; y++) std::cout << 'R';
    }
    std::cout << '\n';

    return;
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
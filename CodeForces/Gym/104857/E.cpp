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
    int n = 0, m = 0;
    std::cin >> n >> m;
    
    std::unordered_map<int, vct<int>> x{}, y{};
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int a = 0;
            std::cin >> a;
            x[a].push_back(i);
            y[a].push_back(j);
        }
    }
    

    auto cnt = [&](vct<int> &a) -> i64
    {
        vct<i64> pre(a.size() + 1, 0);
        for (int i = 1; i <= a.size(); i++)
            pre[i] = pre[i - 1] + a[i - 1];
        
        i64 res = 0;
        for (int i = 0; i < a.size(); i++)
        {
            res += a[i] * i - pre[i];
            res += (pre[a.size()] - pre[i]) - (a.size() - i) * a[i];
        }
        return res;
    };

    i64 ans = 0;
    for (auto &[id, v] : x)
        ans += cnt(v);
    for (auto &[id, v] : y)
    {
        std::sort(v.begin(), v.end());
        ans += cnt(v);
    }
    std::cout << ans << '\n';
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
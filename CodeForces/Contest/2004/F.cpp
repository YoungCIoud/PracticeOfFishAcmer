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
    vct<int> pre(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> pre[i];
        pre[i] += pre[i - 1];
    }

    i64 ans = 0;
    std::map<int, int> cnt;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            ans += j - i - 1;
            ans -= cnt[pre[j] - pre[i]];
            cnt[pre[j] - pre[i]]++;
        }
    }
    std::cout << ans << '\n';
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
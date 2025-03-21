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
    int n = 0, k = 0;
    std::cin >> n >> k;
    vct<int> a(n);
    for (auto &i : a) std::cin >> i;
    std::sort(a.begin(), a.end(), std::greater<int>());

    i64 ans = 0;
    for (int i = 0; i < n; i += 2)
    {
        if (i + 1 >= n)
        {
            ans += a[i];
        }
        else
        {
            int d = std::min(k, a[i] - a[i + 1]);
            k -= d, a[i + 1] += d;
            ans += a[i] - a[i + 1];
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
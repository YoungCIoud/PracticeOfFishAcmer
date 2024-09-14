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
    vct<int> a(100 + 5, 0);
    for (int i = 0; i < 2; i++)
    {
        int l = 0, r = 0;
        std::cin >> l >> r;
        for (int j = l; j <= r; j++) a[j]++;
    }
    
    int cnt2 = 0, cnt12 = 0;
    for (int i = 1; i <= 100; i++)
    {
        if (a[i] == 2)
        {
            cnt2++;
            if (a[i - 1] == 1) cnt12++;
            if (a[i + 1] == 1) cnt12++;
        }
    }
    
    std::cout << std::max(1, cnt2 - 1 + cnt12) << '\n';
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
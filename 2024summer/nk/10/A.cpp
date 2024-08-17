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
    str s;
    std::cin >> s;
    int ny = 0, nn = 0;
    for (auto & i : s)
    {
        if (i == 'Y') ny++;
        else if (i == 'N') nn++;
    }
    if (ny >= 4) std::cout << 1;
    else if (nn >= 2) std::cout << -1;
    else std::cout << 0;
}

int main()
{
    //IOS;
    int t = 1;
    //std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
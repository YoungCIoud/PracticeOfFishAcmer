#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

bool solve()
{
    i64 n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;
    i64 sum = 0;
    for (int i = 0; i < n; i++)
    {
        int u = 0;
        std::cin >> u;
        sum += u - 1;
    }
    for (int i = 0; i < n; i++)
    {
        int u = 0;
        std::cin >> u;
    }
    sum = std::min(m - 1, sum);
    return sum < k;
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        puts(solve() ? "YES" : "NO");
    }

    system("pause");

    return 0;
}
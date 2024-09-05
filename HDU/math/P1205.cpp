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
    int n = 0;
    std::cin >> n;
    i64 sum = 0;
    int mx = 0;
    for (int i = 0; i < n; i++)
    {
        int a = 0;
        std::cin >> a;
        sum += a;
        mx = std::max(a, mx);
    }
    sum -= mx;
    return sum >= mx - 1;
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        puts(solve() ? "Yes" : "No");
    }

    system("pause");

    return 0;
}
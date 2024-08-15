#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

int main()
{
    //IOS;
    int t = 1;
    //std::cin >> t;
    
    while (t--)
    {
        int n = 0, m = 0, k = 0;
        std::cin >> n >> m >> k;
        if (n > m) std::swap(n, m);

        auto cnt = [&](int a, int b) -> i64
        {
            return (i64)a * (a - 1) * b * (b - 1) / 4;
        };

        i64 ans = 0;
        for (int a = (k + m - 1)/ m; a <= n && a <= k; a++)
        {
            int b = k / a;
            
            i64 s1 = cnt(a ,b), s2 = cnt(b + 1, k - a * b), s3 = cnt(b, k - a * b);
            ans = std::max(ans, s1 + s2 - s3);
        }

        std::cout << ans << '\n';
    }

    system("pause");

    return 0;
}
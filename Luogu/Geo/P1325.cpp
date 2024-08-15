#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr double M = 1e7;

int main()
{
    //IOS;
    int t = 1;
    //std::cin >> t;
    
    while (t--)
    {
        int n, d;
        std::cin >> n >> d;
        vct<ary<int, 2>> a(n);
        for (auto& [x, y] : a) std::cin >> x >> y;
        sort(a.begin(), a.end(), [](ary<int, 2> x, ary<int, 2> y){
            if (x[0] == y[0]) return x[1] < y[1];
            else return x[0] < y[0];
        });

        int ans = 0;
        for (auto& [x, y] : a)
            if (y > d) ans = -1;

        if (~ans)
        {
            double R = M;

            a.push_back( { (int)M, d } );
            for (int i = 0; i <= n; i++)
            {
                auto [x ,y] = a[i];
                double t = sqrt(d * d - y * y);
                double l = 1.0 * x - t, r = 1.0 * x + t;
                if (l > R)
                {
                    ans++;
                    R = r;
                }
                else
                {
                    R = std::min(R, r);
                }
            }
        }

        std::cout << ans << '\n';
    }

    system("pause");

    return 0;
}
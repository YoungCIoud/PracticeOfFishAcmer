#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void read(ary<int, 2>& a)
{
    char c;
    std::cin >> c >> a[0] >> c >> a[1] >> c;
}

ary<int, 2> v(ary<int, 2> a, ary<int, 2> b)
{
    return { a[0] - b[0], a[1] - b[1] };
}

int cross(ary<int, 2> a, ary<int, 2> b)
{
    return a[0] * b[1] - b[0] * a[1];
}


int main()
{
    //IOS;
    int t = 1;
    //std::cin >> t;
    
    while (t--)
    {
        ary<int, 2> a[3], x{};
        read(a[0]), read(a[1]), read(a[2]), read(x);

        int pos = 0, neg = 0;
        for (int i = 0; i < 3; i++)
        {
            int t = cross(v(a[i], a[(i + 1) % 3]), v(a[i], x));
            if (t > 0) pos++;
            if (t < 0) neg++;
        }

        int ans = 0;
        if (pos == 3 || neg == 3) ans = 1;
        else if (pos > 0 && neg > 0) ans = 2;
        else if (pos + neg == 2) ans = 3;
        else ans = 4;
        std::cout << ans << '\n';
    }

    system("pause");

    return 0;
}
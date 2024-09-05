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
    IOS;
    int c = 0, n = 0;
    // c <= n
    while ((std::cin >> c >> n) && c)
    {
        vct pos(c, vct<int>{});
        int pre = 0;
        pos[0].push_back(0);
        for (int i = 1; i <= n; i++)
        {
            int a = 0;
            std::cin >> a;
            pre += a;
            pre %= c;
            pos[pre].push_back(i);
        }

        int ans = 0;
        while (pos[ans].size() <= 1) ans++;
        for (int i = pos[ans][0] + 1; i <= pos[ans][1]; i++)
            std::cout << i << " ";
        std::cout << '\n';
    }

    system("pause");

    return 0;
}
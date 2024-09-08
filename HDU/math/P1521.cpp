#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 10, M = 1e5;

i64 f(int n, int m)
{
    if (n > m) std::swap(n, m);
    i64 ans = 1;
    for (int i = 1; i <= n; i++)
        ans = ans * (m + i) / i;
    return ans;
}

int main()
{
    int n = 0, m = 0, sum = 0;
    while(std::cin >> n >> m)
    {
        sum = 0;
        vct<int> cnt(n);
        for (auto& i : cnt)
        {
            std::cin >> i;
            sum += i;
        }

        vct<i64> c1(sum + 1, 0), c2(sum + 1, 0);
        for (int i = 0; i <= cnt[0]; i++) c1[i] = 1;
        for (int k = 1; k < n; k++)
        {
            for (int i = 0; i <= sum; i++)
                for (int j = 0; j <= cnt[k]; j++)
                    if(c1[i]) c2[i + j] += c1[i] * f(i, j);
            for (int i = 0; i <= sum; i++)
                c1[i] = c2[i], c2[i] = 0;
        }

        std::cout << c1[m] << '\n';
    }

    system("pause");

    return 0;
}
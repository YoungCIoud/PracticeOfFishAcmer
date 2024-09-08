#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 35, M = 1e5;


int main()
{
    vct<i64> C(N + 1);
    C[0] = C[1] = 1;
    for (int i = 2; i <= N; i++)
        for (int j = 0; j < i; j++)
            C[i] += C[j] * C[i - 1 - j];

    int t = 1;
    int n = 0;
    while ((std::cin >> n) && n != -1)
        std::cout << t++ << " " << n << " " << C[n] * 2 << '\n';

    system("pause");

    return 0;
}
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7, Inf = 1e18;
constexpr int N = 1e6, M = 1e5;
int C[N + 5];
int qpow(int a, int p)
{
    int res = 1;
    for (; p; p >>= 1, a = 1ll * a * a % Mod)
        if (p & 1) res = 1ll * res * a % Mod;
    return res;
}

int inv(int a)
{
    return qpow(a, Mod - 2);
}

void init()
{
    C[0] = 1;
    for (int i = 1; i <= N; i++)
        C[i] = 1ll * (4ll * i - 2ll) * C[i - 1] % Mod * inv(i + 1) % Mod;
}


int main()
{
    init();

    //IOS;
    int t = 1;
    std::cin >> t;

    for (int i = 1; i <= t; i++)
    {
        int n = 0;
        std::cin >> n;
        printf("Case #%d:\n%d\n", i, C[n]);
    }

    system("pause");

    return 0;
}
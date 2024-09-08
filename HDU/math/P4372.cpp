#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7, Inf = 1e18;
constexpr int N = 2000, M = 1e5;

int C[N + 5][N + 5], S[N + 5][N + 5];

void init()
{
    C[0][0] = S[0][0] = 1;
    for (int i = 1; i <= N; i++)
    {
        C[i][0] = 1, S[i][0] = 0;
        for (int j = 1; j <= i; j++)
        {
            S[i][j] = (S[i - 1][j - 1] + 1ll * (i - 1) * S[i - 1][j] % Mod) % Mod;
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Mod;
        }
    }
}

void solve()
{
    int n = 0, f = 0, b = 0;
    std::cin >> n >> f >> b;
    if (f + b - 1 > n)
        std::cout << 0 << '\n';
    else
        std::cout << 1ll * C[f + b - 2][f - 1] * S[n - 1][f + b - 2] % Mod << '\n';
}

int main()
{
    init();

    //IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
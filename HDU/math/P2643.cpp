#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 20090126, Inf = 1e18;
constexpr int N = 100, M = 1e5;

int fac[N + 5], S[N + 5][N + 5];

void init()
{
    S[0][0] = 1;
    fac[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        fac[i] = 1ll * fac[i - 1] * i % Mod;

        S[i][0] = 0;
        for (int j = 1; j <= i; j++)
            S[i][j] = (1ll * S[i - 1][j - 1] + 1ll * j * S[i - 1][j]) % Mod;
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (1ll * ans + 1ll * S[n][i] * fac[i]) % Mod;
    std::cout << ans << '\n';
}

int main()
{
    //IOS;
    init();

    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
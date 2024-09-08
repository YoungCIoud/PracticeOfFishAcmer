#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7, Inf = 1e18;
constexpr int N = 1e6, M = 1e5;

i64 qpow(i64 a, int p)
{
    i64 res = 1;
    for (; p; a = a * a % Mod, p >>= 1)
        if (p & 1) res = res * a % Mod;
    return res;
}

i64 inv(int a)
{
    return qpow(a, Mod - 2);
}

signed main()
{
    IOS;
    // 阶乘
    vct<i64> fac(N + 5, 0);
    fac[0] = 1;
    for (int i = 1; i <= N; i++)
        fac[i] = fac[i - 1] * i % Mod;
    // 阶乘逆元
    vct<i64> ifac(N + 5, 0);
    ifac[N] = inv(fac[N]);
    for (int i = N; i >= 1; i--)
        ifac[i - 1] = ifac[i] * i % Mod;

    auto C = [&](int n, int m) -> i64
    {
        if (n < m || n < 0 || m < 0) return 0;
        if (n == 0 || m == n) return 1;
        return fac[n] * ifac[n - m] % Mod * ifac[m] % Mod;
    };

    int n = 0;
    str s{};

    while (std::cin >> n >> s)
    {
        i64 ans = -1;
        if (n & 1) ans = 0;
        int a = 0, b = 0;
        for (char &c : s)
        {
            if (c == '(') a++;
            else b++;

            if (b > a)
            {
                ans = 0;
                break;
            }
        }
        a = (n >> 1) - a;
        b = (n >> 1) - b;
        if (a < 0 || b < 0) ans = 0;

        if (ans == -1)
        {
            ans = C(a + b, a) - C(a + b, a - 1) + Mod;
            ans %= Mod;
        }

        std::cout << ans << '\n';
    }

    system("pause");

    return 0;
}
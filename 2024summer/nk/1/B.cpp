// 排列组合 第二类斯特林数
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int N = 5e3, M = 1ll << 32, Inf = 1e16, Mod = 1e9 + 7;
int n, m, q;
int c[N + 5][N + 5]; // 组合数
int s[N + 5][N + 5]; // 第二类斯特林数,s[i][j]表示将i个不同的球分到j个盒子里
int fac[N + 5]; // 阶乘
int pwr[N + 5]; // 幂
void init()
{
    fac[0] = 1 % q, s[0][0] = 1, c[0][0] = 1 % q, pwr[0] = 1 % q;
    for (int i = 1; i <= N; i++)
    {
        fac[i] = fac[i - 1] * i % q;
        c[i][0] = 1 % q;
        for (int j = 1; j <= N; j++)
        {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % q;
            s[i][j] = (s[i - 1][j] * j % q + s[i - 1][j - 1]) % q;
        }
    }
}

int qpow(int a, int p)
{
    int res = 1 % q;
    for (; p; p >>= 1, a = a * a % q)
    {
        if (p & 1)
            res = res * a % q;
    }
    return res;
}

signed main()
{
    std::cin >> n >> m >> q;
    init();

    int ans = 0;
    for (int k = 2; k <= n; k++)
    {
        int res = qpow((qpow(2, k) - 1 + q) % q, m - 1);
        int p = (qpow(2, k) + q - 1 - k) % q;
        for (int i = 1; i <= m; i++)
            pwr[i] = pwr[i - 1] * p % q;

        for (int t = k; t < m; t++)
        {
            res = res + q - c[m - 1][t] * s[t][k] % q * fac[k] % q * pwr[m - 1 - t] % q;
            res %= q;
        }
        res = res * c[n][k] % q * qpow(2, (n - k) * (m - 1)) % q;
        ans = (res + ans) % q;
    }
    std::cout << ans;
    return 0;
}
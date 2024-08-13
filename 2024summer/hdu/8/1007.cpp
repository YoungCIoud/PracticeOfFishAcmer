#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

i64 mul(i64 a, i64 b, i64 m = Inf)
{
    return (i128)a * b % m;
}

i64 qpow(i64 a, i64 p, i64 m = Inf)
{
    i64 res = 1;
    for (; p; p >>= 1, a = mul(a, a, m))
        if (p & 1) res = mul(res, a, m);
    return res;
}

bool miller_rabin(i64 x)
{
    if (x < 2) return false;
    if (x % 2 == 0) return x == 2;

    i64 t = x - 1;
    int k = 0;
    for (; t % 2 == 0; t >>= 1, k++);
    static vct<i64> test = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 };
    for (auto a : test)
    {
        if (a % x == 0) continue;

        a = qpow(a, t, x);
        if (a == 1 || a == x - 1) continue;

        for (int i = 0; i < k; i++)
        {
            i64 lst = a;
            a = mul(a, a, x);
            if (a == 1)
            {
                if (lst != x - 1) return false;
                break;
            }
        }
        if (a != 1) return false;
    }
    return true;
}

std::mt19937_64 rnd(time(0));

i64 pollard_rho(i64 x)
{
    i64 c = rnd() % (x - 1) + 1;
    i64 a = 0, b = 0, val = 1;
    for (int k = 1; ; k <<= 1, b = a, val = 1)
    {
        for (int i = 1; i <= k; i++)
        {
            a = (mul(a, a, x) + c) % x;
            val = mul(val, abs(a - b), x);
            if (i % 127 == 0)
            {
                i64 d = std::__gcd(val, x);
                if (d > 1) return d;
            }
        }
        i64 d = std::__gcd(val, x);
        if (d > 1) return d;
    }
}

vct<i64> fac;
void divide(i64 x)
{
    if (x <= 1) return;
    if (miller_rabin(x))
    {
        fac.push_back(x);
        return;
    }

    i64 y = x;
    while (y == x) y = pollard_rho(x);
    divide(x / y), divide(y); 
}

int f(i64 x)
{
    int res = 0;
    while (x)
    {
        res += x % 10;
        x /= 10;
    }
    return res;
}

i64 a = 0, b = 0, c = 0, ans = 0;

bool check(i64 a, i64 b, i64 c, i64 k)
{
    while (a || b || c) 
    {
        int cura = a % k, curb = b % k, curc = c % k;
        if ((cura + curb) % k != curc) return false;
        a /= k;
        b /= k;
        c /= k;
    }
    return true;
}
void dfs(int cur, i64 val)
{
    if (cur >= fac.size())
    {
        if (val >= 2 && check(a, b, c, val))
        {
            ans++;
            //std::cout << val << '\n';
        }
        return;
    }

    int nex = cur;
    while (nex < fac.size() && fac[cur] == fac[nex]) nex++;
    //dfs(nex, sm, val);
    for (int i = cur; i <= nex; i++)
    {
        dfs(nex, val);
        val *= fac[cur];
    }
}

void solve()
{
    std::cin >> a >> b >> c;
    if (a + b == c)
    {
        std::cout << -1 << '\n';
        return;
    }
    ans = 0;
    fac.clear();
    divide(a + b - c);
    std::sort(fac.begin(), fac.end());
    dfs(0, 1);
    std::cout << ans << '\n';
}

int main()
{
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
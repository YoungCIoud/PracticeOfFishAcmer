#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e6;

i64 mul(i64 a, i64 b, i64 m = Inf)
{
    return (i128)a * b % m;
}

i64 qpow(i64 a, i64 p, i64 m = Inf)
{
    i64 res = 1;
    for(; p; p >>= 1, a = mul(a, a, m))
    {
        if (p & 1)
        {
            res = mul(res, a, m);
        }
    }
    return res;
}

bool miller_rabin(i64 p)
{
    if (p < 2) return false;
    if (p % 2 == 0) return p == 2;
    
    i64 t = p - 1;
    int k = 0;
    for (; t % 2 == 0; t >>= 1, k++);

    static vct<int> test = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 };
    for (auto& x : test)
    {
        if (x % p == 0) continue;

        i64 a = qpow(x, t, p);
        if (a == 1 || a == p - 1) continue;
        for (int i = 0; i < k; i++)
        {
            i64 lst = a;
            a = mul(a, a, p);
            if (a == 1)
            {
                if (lst != p - 1) return false;

                break;
            }
        }

        if (a != 1) return false;
    }
    return true;
}

std::mt19937_64 rnd(time(0));


i64 pollard_rho(i64 n)
{
    i64 c = rnd() % (n - 1) + 1;
    i64 x = 0, y = 0, s = 1;
    for (int k = 1;; k <<= 1, y = x, s = 1)
    {
        for (int i = 1; i <= k; i++)
        {
            x = (mul(x, x, n) + c) % n;
            s = mul(s, abs(x - y), n);
            if (i % 127 == 0)
            {
                i64 d = std::__gcd(s, n);
                if (d > 1) return d;
            }
        }
        i64 d = std::__gcd(s, n);
        if (d > 1) return d;
    }
}

i64 fac;
void find(i64 n)
{
    if (n == 1) return;
    if (miller_rabin(n))
    {
        fac = std::max(fac, n);
        return;
    }

    i64 p = n;
    //if (p == 4) p = 2;
    while (p == n)
       p = pollard_rho(n);

    while (n % p == 0) n /= p;
    find(p), find(n);
}

int main()
{
    //IOS;

    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        i64 n;
        std::cin >> n;
        fac = 0;
        find(n);
        if (fac == n)
        {
            puts("Prime");
        }
        else 
        {
            std::cout << fac << '\n';
        }
    }

    system("pause");

    return 0;
}
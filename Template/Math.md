## gcd
**递归版**
```c++
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}
```
**循环版**
```c++
int gcd(int a, int b)
{
    while (b)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
```

## 快速幂
```c++
i64 qpow(i64 a, i64 p, i64 mod)
{
    i64 res = 1;
    for (; p; p >>= 1, a = a * a % mod)
        if (p & 1) res = res * a % mod;
    return res;
}
```

## 逆元
**费马小定理**
```c++
// a 在模p(质数)下的逆元
i64 inv(i64 a, i64 p)
{
    return qpow(a, p - 2, p);
}
```

## miller-rabin 质数检测

将费马小定理中的指数$p - 1$(一个偶数)分解为$2 ^ k t(t\%2=1)$.  
然后对于每轮测试的底数$x$, 先求出$a = x^{t}$, 再对这个值进行$k$次累乘操作(最终会得到$a^{2^k} = x^{2^kt} = a ^{p - 1}$).

可以得到以下判定:
1. 根据费马小定理,若最终的结果不是1即$a ^{p - 1} \not= 1$, 那么可以判断p一定不是质数.
2. 根据二次探测定理, 在自乘的过程中($a^{'} = a\times a  \% p$), 如果发现$a^{'}=1$而$a\not= n - 1 \And a \not= 1$(即$a^{2} \equiv 1(modp)$的有$1$和$p - 1$之外的解),就能判定$p$一定不是质数.

代码:
```cpp
// 写快速幂和相乘的时候一定要注意爆i64的情况, 此时用i128
bool miller_rabin(i64 p)
{
    // 先过滤掉偶数
    if (p < 2) return false;
    if (p % 2 == 0) return p == 2;
    // 测试用的底数
    static std::vector<i64> test = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 };
    i64 t = p - 1, k = 0;
    for (; t % 2 == 0; k++, t >>= 1);
    for (auto x : test)
    {
        if (x % p == 0) continue;
        i64 a = qpow(x, t, p);
        // 若a等于以下值, 接下来累乘的结果就都是1了.
        if (a == 1 || a == p - 1) continue;
        for (int j = 0; j < k; j++)
        {
            i64 lst = a;
            // 二次探测定理
            a = mul(a, a, p);
            if (a == 1)
            {
                if (lst != p - 1)
                    return false;
                break;
            }
        }
        //费马小定理
        if (a != 1) return false;
    }
    return true;
}
```
关于检测时使用的底数,在待检验数在$2^{32}$以下时用{ 2 ,7 ,61 }就可以了,否则用{ 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }.

## 快速因数分解 Pollard's Rho
```cpp
// 随机数
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
```
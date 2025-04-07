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
**拓展欧几里得求逆元**


```cpp
// 返回gcd(a,b)
int extend_gcd(long long a, int b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int res = extend_gcd(b, a % b, x, y);

    int t = x;
    x = y;
    y = t - (a / b) * y;

    return res;
}

// 求a关于p的逆元
long long inv(long long a, int p)
{
    long long x = 0, y = 0;
    extend_gcd(a, p, x, y);

    return (x % p + p) % p;
}
```

## 随机数
```c++
std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
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

## 容斥原理的应用:求区间内和某一个数互质的数的个数

首先对于一个质数$p$, 我们可以很快地找到在区间[1, n]内有多少数和他不互质($\lfloor \frac{n}{p} \rfloor$), 用n减去这个数就得到了区间内和$p$互质的数的个数.

那么对于任意一个数$q$, 我们可以求得他所有的质因数$p_0,p_1,...,p_k$. 接下来用容斥原理反向求区间内跟这些数都不互质的数的个数问题就解决了.

```cpp
// 返回[1,n]内有多少个数同m互质
i64 cnt(int n, int m)
{
    // 求m的质因数
    num = 0;
    for (int i = 2; i * i <= m; i++)
    {
        if (m % i) continue;
        while (m % i == 0) m /= i;
        pr[num++] = i;
    }
    if (m != 1) pr[num++] = m;

    // 区间内和m不互质的数的个数
    i64 res = 0;
    // 枚举质因数的组合情况
    for (int i = 1; i < (1 << num); i++)
    {
        int p = 1, cnt = 0;
        for (int j = 0; j < num; j++)
            if ((i >> j) & 1) p *= pr[j], cnt++;
        // 容斥
        // 若是奇数个质因数组合, 则+
        // 否则-
        if (cnt & 1) res += n / p;
        else res -= n / p;
    }

    return n - res;
}
```

## 母函数的应用:整数划分

观察以下式子:
$$
\prod_{k = 1}^{n}(\sum_{i = 0}^{ik \leq n}x^{ik}) = 
(x^{0\times1} + x^{1\times1} + x^{2\times1} + ...)
(x^{0\times2} + x^{1\times2} + x^{2\times2} + ...)
(x^{0\times3} + x^{1\times3} + x^{2\times3} + ...)
$$
其中,$(x^{0\times1} + x^{1\times1} + x^{2\times1} + ...)$的含义是1用0次,1用1次,1用2次以此类推.此函数展开后,第$x^n$的系数就是数字$n$的划分数.  
代码要做的就是模拟手工计算:
```cpp
for (int i = 0; i <= N; i++)
    c1[i] = 1, c2[i] = 0;
    
for (int k = 2; k <= N; k++)
{
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= N; j += k)
            c2[i + j] += c1[i];
    // 更新计算结果
    for (int i = 0; i <= N; i++)
        c1[i] = c2[i], c2[i] = 0;
}
```

以上是普通的母函数,可用于求组合方案数.还有一种指数型母函数可以用于求排列数([模板hdu1521](https://acm.hdu.edu.cn/showproblem.php?pid=1521)).

## Catalan数

**定义**  
$C_n=\frac{1}{n + 1}C_{2n}^{n}$

**模型**
1. $C_n =\frac{1}{n + 1}C_{2n}^{n} = C_{2n}^{n} - C_{2n}^{n + 1} = C_{2n}^{n} - C_{2n}^{n - 1}$. 可以看作把n个0和n个1排成一行,使得这一行任意前k个数中1的数量总是大于0的数量的排列的个数.
2. $C_n = \sum_{k = 0}^{n - 1} C_kC_{n-1-k}, C_0 = 1$

关于模型1的一种推导:  
在直角坐标系中, 我们从(0, 0)想要走到(n,n), 每次都能向上或向右. 要求形成的路径在主对角线(y=x)右下方(可以有点落在主对角线上),求这样的路径数(其实这个问题和01排成一行的问题是等价的)

对于跨过主对角线y=x的路径,肯定会与y=x+1有交点.
我们找到第一个与y=x+1的交点, 交点之前的路径不变,交点之后的路径我们做出它关于y=x+1对称的路径, 新路径的终点肯定是在(n+1,n-1)(对称性).
也就是说,跨过主对角线的路径和一条到(n+1,n-1)的路径对应.

所以我们要求的路径数就是总的路径数减去到(n+1,n-1)的路径数:$C_{2n}^{n} - C_{2n}^{n + 1} = \frac{1}{n + 1}C_{2n}^{n}$


**计算公式**
1. $C_n = \sum C_kC_{n-1-k}, C_0 = 1$
2. $C_n = \frac{4n-2}{n+1}C_{n-1}$
3. $C_n=\frac{(2n)!}{(n+1)!n!}$

公式1适用于n比较小且需要直接输出Catalan数的情况,
公式2和公式3适用于n非常大的情况.

## Stirling数
**第一类**  
$S(n,k)$定义为把$n$个不同的元素分配到k个圆排列里且圆不为空的方案数. 有递推式:
$$
S(n,k) = S(n - 1, k - 1) + (n - 1)S(n - 1, k), 1\leq k \leq n
$$
且$$S(0,0) = 1, S(n, 0) = 0,1 \leq n$$


**第二类**  
$S(n,k)$定义为把$n$个不同的元素分配到k个相同的箱子里且箱子不为空的方案数. 有递推式:
$$
S(n,k) = S(n - 1, k - 1) + kS(n - 1, k), 1\leq k \leq n
$$
且$$S(0,0) = 1, S(n, 0) = 0,1 \leq n$$

## Lucas 定理

```cpp
class Lucas {
private:
    int mod;
    std::vector<i64> fa, ifa;
    
    int cnt(int n, int m) {
        if (n < m) {
            return 0;
        }
        return fa[n] * ifa[m] * ifa[n - m] % mod;
    }
public:
    // 根据模数预处理阶乘和阶乘逆元
    Lucas(int m): mod(m) {
        fa.assign(mod, 1ll);
        for (int i = 1; i < mod; i++) {
            fa[i] = fa[i - 1] * i % mod;
        }
        ifa.assign(mod, mod - 1); // 威尔逊定理
        for (int i = mod - 1; i > 0; i--) {
            ifa[i - 1] = ifa[i] * i % mod;
        }
    }

    int C(int n, int m) {
        i64 res = 1;
        while (m) {
            (res *= cnt(n % mod, m % mod)) %= mod;
            n /= mod;
            m /= mod;
        }
        return res;
    }
};
```

## 二维平面中曼哈顿距离与切比雪夫距离的相互转换

$$
\begin{aligned}
M(u, v) &= |x_1 - x_2| + |y_1 - y_2| \\
&= \max\{ x_1 - x_2 + y_1 - y_2, x_2 - x_1 + y_1 - y_2, x_1 - x_2 + y_2 - y_1, x_2 - x_1 + y_2 - y_1\} \\
&= \max\{|(x_1 + y_1) - (x_2 + y_2)|, |(x_1 - y_1) - (x_2 - y_2)| \} \\
&= Q((x_1 + y_1, x_1 - y_1), (x_2 + y_2, x_2 - y_2))
\end{aligned}
$$

## 求勾股数

```cpp
// 以 c 索引
std::vector<std::array<int, 2>> R[MXR + 5];
void solve()
{
    for (int i = 1; i * i <= MXR; i++) {
        for (int j = 1; j < i && i * i + j * j <= MXR; j++) {
            if ((i + j) % 2 == 0 || std::__gcd(i, j) != 1) {
                continue;
            }

            int a = 2 * i * j;
            int b = i * i - j * j;
            int c = i * i + j * j;
            for (int k = 1; c * k <= MXR; k++) {
                R[c * k].push_back({ a * k, b * k });
            }
        }
    }
}
```

## 快速傅里叶变换 FFT
```cpp
// M 多项式最大的长度
std::vector<int> idx(M << 2);
void fft(int len, std::vector<std::complex<double>> &A, int inv) {
    for (int i = 1; i < len; i++) {
        if (i < idx[i]) {
            std::swap(A[i], A[idx[i]]);
        }
    }

    for (int mid = 1; mid < len; mid <<= 1) {
        std::complex<double> unit(cos(M_PI / mid), inv * sin(M_PI / mid));
        for (int l = 0; l < len; l += (mid << 1)) {
            std::complex<double> w(1.0, 0.0);
            for (int i = 0; i < mid; i++, w *= unit) {
                std::complex<double> x(A[i | l]), y(w * A[i | l | mid]);
                A[i | l] = x + y;
                A[i | l | mid] = x - y;
            }
        }
    }

    for (int i = 0; inv == -1 && i < len; i++) {
        A[i] /= len;
    }
    return;
}

// 传两个多项式返回这两个多项式相乘（卷积）的结果
std::vector<i64> converlution(std::vector<i64> &a, std::vector<i64> &b) {
    int la = a.size() - 1, lb = b.size() - 1;
    int len = 1;
    // 长度是 2 的幂且必须大于最高次数
    while (len <= la + lb) {
        len <<= 1;
    }
    
    for (int l = 1, r = 1, bit = len >> 1; l < len; l <<= 1, bit >>= 1) {
        for (int i = 0; i < l; i++) {
            idx[r++] = idx[i] | bit;
        }
    }

    std::vector<std::complex<double>> A(len);
    for (int i = 0; i < len; i++) {
        A[i] = std::complex<double>(i <= la ? a[i] : 0.0, i <= lb ? b[i] : 0.0);
    }
    fft(len, A, 1);
    for (int i = 0; i < len; i++) {
        A[i] = A[i] * A[i];
    }
    fft(len, A, -1);

    std::vector res(la + lb + 1, 0ll);
    for (int i = 0; i <= la + lb; i++) {
        res[i] = i64(A[i].imag() / 2.0 + 0.5);
    }
    return res;
}

```
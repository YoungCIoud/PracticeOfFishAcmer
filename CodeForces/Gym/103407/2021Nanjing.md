## I. Cloud Retainer's Game

### 题目大意

在平面直角坐标系 $\{(x, y) |1 \le x \And 1 \leq y \le H\}$ 的区域中有 $n$ 个隔板和 $m$ 个硬币，
你初始在原点且速度向量为 $(1,1)$ ，
当以速度 $(a,b)$ 碰到隔板或边界后，
速度变为 $(a,-b)$ 。
假设你能无限制地忽略隔板，
问最优能碰到多少个硬币。

### 题解

#### 解题思路

先考虑没有隔板的情况。
从原点出发形成的路径是一条被限制在边界内折线，
且折线的每段线段都可以被表示为 $y = kx + b(k \in \{ 1, -1\})$。
观察相邻的两条斜率相同的线段，
可以发现 $|\Delta b| = 2H$。
也就是说如果我此刻正沿着直线 $y = kx + b$ 运动，
那么我后面一定会到达直线 $y = kx + b + 2Ht(t \in \Nu)$。
所以我们可以把这样的直线归为一类： $(x - \frac{y}{k} + 2H) \% 2H = K$。
推一推公式能发现在同一条折线中的线段不管斜率相不相同都满足上面的式子。  
这样就能把所有的线都囊括在 $K$ 中。

则将所有的点排好序后，
遍历一遍。
若碰到硬币，
则尝试将两种可以到达该硬币的折线碰到的硬币数加 1 ；
若碰到隔板，
两折线的碰到的硬币数取最大。  
根据排序方式的不同有不同的具体实现。
若将点从左下到右上排序，
则需注意能够达到某条折线的问题（具体看代码），
最后对所有折线碰到的硬币取最大值。
若将点从右上到左下排序，
则直接操作就好了，
最后直接输出 $K = 0$ 的折线碰到了多少节点。

下面给出从左下到右上排序的做法
#### CODE
```cpp
void solve()
{
    int h = 0, n = 0;
    std::cin >> h >> n;
    std::vector a(n, std::pair<Node, bool>{});
    for (auto &[p, block] : a) {
        std::cin >> p.first >> p.second;
        block = true;
    }
    
    int m = 0;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        Node p;
        std::cin >> p.first >> p.second;
        a.push_back({ p, false });
    }

    std::sort(a.begin(), a.end());
    std::unordered_map<int, int> dp;
    dp[0] = 0;
    for (auto &[p, block] : a) {
        auto &[x, y] = p;
        int sla = (x + y) % (2 * h), bas = (x - y) % (2 * h);
        if (block) {
            if (dp.count(sla) || dp.count(bas))
                dp[sla] = dp[bas] = std::max(dp[sla], dp[bas]);
        }
        else {
            if (dp.count(sla)) dp[sla]++;
            if (dp.count(bas)) dp[bas]++;
        }
    }

    // std::cout << dp[0] << '\n';
    int ans = 0;
    for (auto &[k, num] : dp) {
        ans = std::max(ans, num);
    }
    std::cout << ans << '\n';
}
```

## J. Xingqiu's Joke

### 题目大意

给出两个正整数 $a$ 和 $b$ ，
可以对他们进行同时加减一或除公共质因数的操作，
问最少多少步操作可以将其中一个数变成 1 。

### 题解

#### 解题思路

我们知道可以通过加减 $a$ 和 $b$ 来让他们可以同时被某个数整除，
这是因为我们可以这样表达 $a$ 和 $b$ ：

$$
\begin{cases}
a = pk_1 + d\\
b = pk_2 + d
\end{cases}
\tag{1}
$$

在这种表达下，
对 $a$ 和 $b$ 同时减 $d$ 就可以让它们同时被 $p$ 整除。同时我们注意 $a$ 和 $b$ 的差值，
令 $c = a - b = p(k_2 - k_1)$，
就可以发现 $p | c$。
也就是说 $(1)$ 中所有可能的 $p$ 值都是 $c$ 的因数。  
所以我们预处理出 $c$ 的所有质因数（不超过 10 个）作为待选的除数。

假设 $a<b$ ，
则 $b = a + c$ 。
所以我们只需要 $a$ 和 $c$ 就能知晓当前两个数的值。
相对于考察 $a$ 和 $b$ 的最优解，
肯定更倾向于考察 $a$ 和 $c$ 的最优解。
因为在进行加减操作时，
$c$ 是定值。  
令 $f(a, c)$ 为两个整数为 $a$ 和 $a + c$ 时的最优解，
则 $f(a, c)$ 可由 $f(\lfloor a / p \rfloor, c / p)$ 和 $f(\lceil a / p \rceil, c / p)(p | c)$ 转移而来，
前者是减至 $p|a$ 而后者是加至 $p|a$ 。

记忆化搜索一下就好了。

#### CODE
```cpp
std::vector<int> d;
std::map<std::pair<int, int>, int> mp;
void init(int c) {
    d.clear();
    mp.clear();
    for (int i = 2; i * i <= c; i++) {
        if (c % i == 0) {
            d.push_back(i);
            while (c % i == 0) {
                c /= i;
            }
        }
    }
    if (c > 1) {
        d.push_back(c);
    }
    return;
}

int f(int a, int c) {
    if (a <= 1) {
        return 0;
    }
    if (c == 1) {
        return a - 1;
    }
    if (mp.count({ a, c })) {
        return mp[{ a, c }];
    }

    int res = a - 1;
    for (auto &p : d) {
        if (c % p != 0) {
            continue;
        }

        int up = (a + p - 1) / p;
        res = std::min(res, f(up, c / p) + up * p - a + 1);
        int low = a / p;
        res = std::min(res, f(low, c / p) + a % p + 1);
    }
    mp[{a, c}] = res;
    return res;
}

void solve()
{
    int a = 0, b = 0;
    std::cin >> a >> b;
    if (a > b) {
        std::swap(a, b);
    }
    init(b - a);

    std::cout << f(a, b - a) << '\n';
}
```
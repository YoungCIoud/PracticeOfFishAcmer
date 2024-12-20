# Miao Maio Problem（喵喵题）

## [Alice's Adventures in Addition](https://codeforces.com/contest/2028/problem/F)（dp的优化 bitset）

### 题解（题意见链接）

#### 解题思路

我们可以先想出非常 naive 的 dp：
$dp[i][j] = 0 / 1$ 表示在前 $i$ 个数里插入运算符后的结果能否是 $j$。

于是当 $a_i = 0$ 时我们有如下转移：
$$
dp[i][j] = dp[0][j] \mid dp[1][j] \mid \dots \mid dp[i - 1][j]
$$
因为通过末尾 0 能通过乘法将一段后缀乘成 0，
所以能取到前缀能达到的所有值。  
当 $a_i = 1$ 时：
$$
dp[i][j] = dp[i - 1][j] | dp[i - 1][j - 1]
$$
既在前面的式子后乘一或加一。  
当 $a_i >= 2$ 时，
从 $a_i$ 开始在遇到 0 之前可以一直往前连乘，
设乘到 $a_j$ 连乘得结果是 $prd_j(prd_i = a_i)$， 则：
$$
dp[i][j] = dp[i - 1][j - prd_i] \mid dp[j][j - prd_j] \mid \dots
$$
当遇到第一个（从后往前） $a_k = 0$ 时还有：
$$
dp[i][j] \mid = dp[k][j]
$$
因为连乘到 $a_k$ 时后面一段得结果就变成了 0，
相当于对 $a_k = 0$ 进行转移，
结果已经计算过了就是 $dp[k]$

这样转移的时间复杂度瓶颈在于 $a_i >= 2$ 时枚举连乘（其他所有转移都可以是 $O(1) 的$），
最坏的情况下单次转移可以达到 $O(n)$。  
显然空间复杂度也是不达标的。

$2^{14} > 10^4$ 表明对于大于等于 2 的数最多能连乘 13 次，
再乘下去就超过了给定的 $m$ 是无意义的。
但是在连乘时会出现许多 1 导致连乘次数大于 13。
所以 我们考虑跳过这些 1， 
只关心非 1 非 0 的位置，
这样单次转移最多就是 13 次。

但是$O(13nm)$的复杂仍过不了，
可以通过 bitset 的移位加快第二维的转移，
具体实现看代码。

#### CODE

```cpp
std::deque<std::pair<int, std::bitset<M + 1>>> q; // 非 0 非 1
std::bitset<M + 1> all; // 记录当前为止所有出现过的数
std::bitset<M + 1> cur; // 当前状态
std::bitset<M + 1> lst; // 上一个的状态
std::bitset<M + 1> zero; // 开头到目前为止最后一个0的状态
void init() {
    q.clear();
    all = 1;
    lst = 1;
    zero = 0;
}

void solve()
{
    init();
    int n = 0, m = 0;
    std::cin >> n >> m;
    while (n--) {
        int a = 0;
        std::cin >> a;

        if (a == 0) {
            cur = zero = all;
            q.clear();
        }
        else if (a == 1) {
            cur = lst | (lst << 1);
        }
        else {
            cur = zero;
            q.push_front({ a, lst });
            for (int i = 0, prd = q[i].first; prd <= m; prd *= q[++i].first) {
                cur |= (q[i].second << prd);
                if (i == q.size() - 1) {
                    break;
                }
            }
            while (q.size() >= L) {
                q.pop_back();
            }
        }
        
        lst = cur;
        all |= cur;
    }
    std::cout << (cur[m] ? "Yes" : "No") << '\n';
}
```

## [Natlan Exploring](https://codeforces.com/contest/2037/problem/G)（dp的优化 容斥）

### 题解（题意见链接）

#### 解题思路

首先很容易想到朴素dp：
```c++
// dp[i] 表示从第i个数到第n个数的路径数量
std::vector dp(n + 1, 0ll);
dp[n] = 1;
for (int i = n; i >= 1; i--) {
    for (int j = i + 1; j <= n; j++) {
        if (std::__gcd(a[i], a[j]) != 1) {
            dp[i] += dp[j];
        }
    }
}
```
显然这样 $O(n^2)$ 的 dp 是肯定不行的。 需要考虑优化。

如果我们提取出每个数的质因数， 就可以发现若两个数的 gcd 不为 1 ， 则这两个数必然有相同的质因数。  
所以可以想到， 在已经求出了第 $i$ 个数到第 $n$ 个数的答案 $dp[i]$ 时， 我们还要对 $a[i]$ 进行质因数分解， 并让 $dp[i]$ 加到所有的 $cnt[p]$ 中（ $p$ 是 $a[i]$ 的质因数）。

所以从后往前转移到 $i$ 时， 发现单独让 $\sum_{p是质因数} cnt[p]$ 成为 $dp[i]$ 是肯定大于等于实际值的，因为有的数在 $cnt[p_1]$ 中算了一次又在 $cnt[p_2]$ 中算了一次。 通过容斥就可以轻松解决了， 就需要 $cnt[res]$（$res$ 是 $a[i]$ 质因数所有组合情况的乘积）里加上 $dp[i]$。

在 $M \leq 10^6$ 的情况下， 一个数不同的质因数个数一定小于 7 ， 因为最小的 7 个质数的乘积已经超过 $M$ 了。 所以 $res$ 实际上有小于 $2^7$ 种情况， 再加上质因数分解的复杂度也足够小， We done。

#### CODE
```cpp
void solve()
{
    // 线性筛
    std::vector<int> prime;
    std::vector vis(SM + 1, false);
    for (int i = 2; i <= SM; i++) {
        if (not vis[i]) {
            prime.push_back(i);
        }
        for (auto &p : prime) {
            if (p * i > SM) {
                break;
            }
            vis[p * i] = true;
            if (i % p == 0) {
                break;
            }
        }
    }

    int n = 0;
    std::cin >> n;
    std::vector a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::vector dp(n + 1, 0ll), cnt(M + 1, 0ll);
    dp[n] = 1;
    for (int i = n; i >= 1; i--) {
        // 分解质因数
        std::vector<int> p;
        for (int j = 0; prime[j] * prime[j] <= a[i]; j++) {
            if (a[i] % prime[j] == 0) {
                p.push_back(prime[j]);
                while (a[i] % prime[j] == 0) {
                    a[i] /= prime[j];
                }
            }
        }
        if (a[i] != 1) {
            p.push_back(a[i]);
        }

        // 容斥
        // 枚举质因数的所有组合
        for (auto s = 1; s < (1 << p.size()); s++) {
            bool flag = false;
            int res = 1;
            for (int j = 0; j < p.size(); j++) {
                if (s >> j & 1) {
                    flag = !flag;
                    res *= p[j];
                }
            }
            if (flag) {
                (dp[i] += cnt[res]) %= Mod;
            }
            else {
                (dp[i] += Mod - cnt[res]) %= Mod;
            }
        }
        for (auto s = 1; s < (1 << p.size()); s++) {
            int res = 1;
            for (int j = 0; j < p.size(); j++) {
                if (s >> j & 1) {
                    res *= p[j];
                }
            }
            (cnt[res] += dp[i]) %= Mod;
        }
    }
    std::cout << dp[1] << '\n';
    return;
}
```

## [Chips on a Line](https://codeforces.com/contest/1997/problem/F)（dp好题）

### 题解（题意见链接）

#### 解题思路

最基本， 要观察到题目描述和斐波那契数列之间的关系： 消除相邻的两个可以合成后一个， 消除后一个可以得到相邻的前两个， 即$fab[i] = fab[i - 1] + fab[i - 2]$（斐波那契数列）。  
有了这个观察后， 就可以想到所有的状态（排列）都可以用一个状态数来表示， 具体的： 位于位置 $x$ 的一个 Chip 有值 $fab[x]$， 我们可以把一个状态中所有 $x > 2$ 的 Chip 通过操作 1 移动， 最后肯定只有位置 1 和位置 2 有 Chip， 这两个位置的 Chips 的总和就是我们用来表示状态的状态数。 不难发现， 一个状态数可以对应若干个不同的状态， 但只要状态数相同， 不管状态如何能达到的最小价值就是看组成状态数最少要多少个斐波那契数（可以重复）。

> 证明：  
> 首先状态数相同的两个状态一定可以相互到达，具体的， 可以先把所有的 Chips 都操作到位置 1， 然后通过另一个状态的逆操作到达那个状态。  
> 有因为一个斐波那契数就对应一个位置的 Chip， 根据题目对价值的定义即得证。

所以问题就变成了在前的 $x$ 个斐波那契数中选 $n$ 个（可重复选）， 有多少种选法能让选中数字的和最少能拆分成 $m$ 个斐波那契数。

不考虑选 $n$ 个的话就是一个完全背包问题： 前 $x$ 个斐波那契数每个可以选无数次， 求组成特定的和的方案数。 考虑 $n$ 的条件的话加一维就好了。

求特定的和也是一个完全背包问题。

#### CODE
```cpp
void solve()
{
    int n = 0, x = 0, m = 0;
    std::cin >> n >> x >> m;

    std::vector<int> fab(L + 1, 1);
    for (int i = 3; i <= L; i++) {
        fab[i] = fab[i - 1] + fab[i - 2];
    }

    // dp[i][j] 将数字 i 划分成 j 个数的方案数
    dp[0][0] = 1;
    for (int k = 1; k <= x; k++) {
        for (int i = fab[k]; i <= n * fab[k]; i++) {
            for (int j = 1; j <= n; j++) {
                (dp[i][j] += dp[i - fab[k]][j - 1]) %= Mod;
            }
        }
    }

    std::vector<int> mn(n * fab[x] + 1, Inf);
    mn[0] = 0;
    for (int i = 1; i <= L; i++) {
        for (int j = fab[i]; j <= n * fab[x]; j++) {
            mn[j] = std::min(mn[j], mn[j - fab[i]] + 1);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n * fab[x]; i++) {
        if (mn[i] == m) {
            (ans += dp[i][n]) %= Mod;
        }
    }
    std::cout << ans << '\n';
    
    return;
}
```

## [I Hate Sigma Problems](https://atcoder.jp/contests/abc371/tasks/abc371_e)（组合数学 计数）

### 题解（题意见链接）

#### 解题思路

首先 $f(l,r)$ 的值是由区间内每个不同的数贡献的,
且每个不同的数贡献为1.
如果我们能算出每个数在多少个区间内做了贡献,
问题就得到了解决.

单独考虑一个数 $x$ ,
很容易找出序列中所有 $x$ 出现的下标(为了方便处理, 可以认为所有数都出现在了下标为 $0$ 和 $N + 1$ 的位置),
相邻下标内的区间就是未出现 $x$ 的区间.
用总的区间数减去这个这些区间就是 $x$ 的贡献了.

## [Takahashi in Narrow Road](https://atcoder.jp/contests/abc371/tasks/abc371_f)（模拟技巧）

### 题解（题意见链接）

#### 解题思路

首先有一个技巧可以简单地将连续相邻的人看成一块:
将第 $i$ 个人的坐标减 $i$.
对于每一块我们可以只保留第一个人的坐标.

接下来就是移动的操作了.  
若我们将一个人右移.
那么肯定会形成以这个人开头的新的一块.
移动时要分情况讨论:
1. 若不存在下一块, 就直接将这个人后面的所有人(这些人一定是在一块的)移动到指定位置.
2. 若下一块的位置在指定位置之后, 那就将新的块移动到指定位置.
3. 否则将新的块合并到下一块(注意这步还要将该块的第一个人删掉)上, 此时形成的块的的第一个人仍然是我们指定的人.

#### CODE
```cpp
// idx 是指定的人
// tar 是目标位置
{
    f[idx] = tar;
    it = f.find(idx);
    while (true) {
        auto nxt = std::next(it);
        if (nxt == f.end()) {
            ans += 1ll * (tar - pos) * (n - idx + 1);
            break;
        }
        if (nxt->second > tar) {
            ans += 1ll * (tar - pos) * (nxt->first - idx);
            break;
        }
        ans += 1ll * (nxt->second - pos) * (nxt->first - idx);
        pos = nxt->second;
        f.erase(nxt);
    }
}
```
将一个人左移考虑的方法是一样的, 但实现稍有不同:
```cpp
{
    // idx后形成一个新的块
    if (idx < n && f.count(idx + 1) == false) {
        f[idx + 1] = pos;
    }
    while (true) {
        if (it == f.begin()) {
            ans += 1ll * (pos - tar) * idx;
            break;
        }
        auto prv = std::prev(it);
        if (prv->second < tar) {
            ans += 1ll * (pos - tar) * (idx - it->first + 1);
            break;
        }
        ans += 1ll * (pos - prv->second) * (idx - it->first + 1);
        pos = prv->second;
        f.erase(it);
        it = prv;
    }
    it->second = tar;
    }
```

## [Georgia and Bob](http://poj.org/problem?id=1704)（阶梯博弈）

### 题解（题意见链接）

#### 解题思路

我们先只看 3 个棋子， 则三个棋子会产生 2 段空白格子。 将中间的棋子往左移会导致左边的空白变少而右边的空白变大， 这就等价于在左边的空白中挑选部分移到右边的空白。

有了这点观察后， 问题就变成了给出若干段空白最先将所有空白移到最右边的人输， 基本上就是裸的阶梯博弈了。

#### CODE

```cpp
int main () {
    int t = 1;
    std::cin >> t;
    while (t--) {
        int n = 0;
        std::cin >> n;
        std::vector<int> p(n, 0);
        for (int i = 0; i < n; i++) {
            std::cin >> p[i];
            p[i] = -p[i];
        }
        std::sort(p.begin(), p.end());
        int ans = 0;
        for (int i = 1; i < n; i += 2) {
            // 两个棋子之间的空白格的数量
            ans ^= (p[i] - p[i - 1] - 1);
        }
        if (n & 1) {
            // n 为奇数时， 最左边的棋子左边一段的空白也要算进去
            ans ^= -p.back() - 1;
        }

        std::cout << (ans == 0 ? "Bob" : "Georgia") << " will win\n";
    }
    // system("pause");
    return 0;
}
```

### 拓展

如果最后要将所有的棋子都移到第 0 格， 则继续沿用上述方法， 唯一需要改变的地方是最左边的一段空白要将 0 算进去（原题最左边的空白是 $(0, r)$，而改条件后最左边的空白是 $[0, r)$）。

可以沿用上述方法的原因是等价关系依旧成立。

## [Climbing the Hill](https://acm.hdu.edu.cn/showproblem.php?pid=4315)（更难一点的阶梯博弈）

### 题解（题意见链接）

#### 解题思路

首先当 $k = 1$ 时就可以直接出答案了， 当 $k = 2$ 时， 肯定有个状态是所有的人都排成连续的一排，且最上面的人差一步登顶， 面临这个状态的人是肯定必输的， 所以当 $k = 2$时跟上面一题是一模一样的。

当 $k > 2$ 时， 必输的状态就是前 $k - 2$（包括） 的人全部登顶， 而剩下的就全部排成连续的一排， 且最上面的人差一步登顶。这就相当于前一部分的条件是上一题的拓展题而后一部分的条件是上一题原题。  
这种情况依然可以直接使用拓展题的代码， 后面一部分的限制还是那句话， 不会影响等价关系。

所以就只用对 2 特判一下就好了

#### CODE

改下上题的输入输出，特判 ``k = 1``， 最后判断的时候这样写就好了：

```cpp
        if (n & 1) {
            ans ^= -p.back() - (k == 2);
        }
```

# Hard Problem（难题）

## [Topology](https://codeforces.com/gym/105484/problem/C)（拓扑序 树形dp 数学）

### 题意

给定一颗有 n 个节点且以 1 为根的外向树， 满足父节点的编号小于儿子的编号， 对于每个 $1 \leq i \leq n$ 求满足第 $i$ 个点在拓扑序的第 i 个位置的拓扑序的数量。

### 题解

假设我们已经知道了当节点 $u$ 在第 $x$ 个位置时且把子树 $u$ 视为一个点时（不考虑子树 $u$ 的拓扑序）整棵树的拓扑序数量 $dp[u][x]$， 则考虑子树 $u$ 的拓扑序后的整颗树的拓扑序数量就是 $dp[u][x] \times C_{n - x}^{size_u - 1} \times cnt_u $。  其中 $C_{n - x}^{size_u - 1}$的意义是： 在确定点 $u$ 在拓扑序中的位置是 $x$ 后， 要在后面的 $n - x$ 个空位里选 $size_u - 1$ 个位置给子树 $u$ 里除了 $u$ 以为的点。 $cnt_u$ 的就是子树 $u$ 的拓扑序数量。 当 $x = u$ 时上面的式子就是我们要求的答案。

排列数预处理就好了， 子树大小和子树内的拓扑序数量也可以在预处理的时候求出。 下面给出一颗有 n 个节点的树的拓扑序数量公式：  
$$
\frac{n!}{ \prod_{i = 1}^{n}{size_i}}
$$

下面考虑如何求 $dp[i][j]$。  
1. 显然 $dp[1][1] = 1$， 意思是将整棵树都看成了一个点， 此时拓扑序的数量自然是 1。
2. 考虑从 $dp[u][x]$ 转移到 $dp[v][y]$（ $u$ 是 $v$ 的父亲且$x < y$）。 此时除了子树 $u$ 以外的所有点的拓扑序数量都是已知的， 所以我们只需要考虑当点 $v$ 在位置 $y$ 且不考虑子树 $v$ 内部的拓扑序时的子树 $u$ 的拓扑序数量， 这个数就是转移系数。 其实就是先给子树 $u$ 内除去点 $u$ 和子树 $v$ 内的点后剩余的点选位置再乘这些剩余点的拓扑序数量。 选位置： $C_{n - x - size_v}^{size_u - 1 - size_v}$。 剩余点的拓扑序数量： 可以通过预处理连乘来根据公式求， 也可以在 $cnt_u$ 的基础上除 $C_{size_u - 1}^{size_v} * cnt_v$ 得到。 所以就得到了转移： $dp[v][y] = dp[v][y] + C_{n - x - size_v}^{size_u - 1 - size_v} \times {cnt_u \over C_{size_u - 1}^{size_v} \times cnt_v} \times dp[u][x]$。 可以发现转移系数跟 $u$ 具体在哪个位置无关， 只用满足 $x < y$ 就好了， 所以还可以通过前缀和来优化。
3. We done!

$cnt_u \over C_{size_u - 1}^{size_v} \times cnt_v$ 就是剩余点拓扑序的数量（记为 $A$ ）， 理由如下：  
首先 $u$ 节点的位置是确定的不做考虑， 当我们已经知道了 $A$ 和 $cnt_v$ 就可以求出 $cnt_u$ 了， 即 $cnt_u = A \times C_{size_u - 1}^{size_v} \times cnt_v$。 排列数的意义是子树 $u$ 除了 $u$ 以外还有 $size_u - 1$ 个位置， 在其中选 $size_v$ 个给子树 $v$ 里的点。

#### CODE
```cpp
i64 init(int cur) {
    siz[cur] = 1;
    i64 inv_mul = 1;
    for (auto &to : g[cur]) {
        (inv_mul *= init(to)) %= Mod;
        siz[cur] += siz[to];
    }
    (inv_mul *= inv(siz[cur])) %= Mod;
    // 子树 cur 的拓扑排序的数量 siz[cur]! * inv_mul;
    cnt[cur] = fac[siz[cur]] * inv_mul % Mod;
    return inv_mul;
}

void dfs(int cur, int fa, int deep) {
    i64 num = cnt[fa] * inv(C[siz[fa] - 1][siz[cur]] * cnt[cur] % Mod) % Mod;
    for (int pos = deep; pos + siz[cur] <= n + 1; pos++) {
        // num 在子树 fa 内去掉子树 cur 后所得的树的拓扑排序的数量
        // num * C[siz[fa] - 1][siz[cur]] * cnt[cur] = cnt[fa]
        if (dp[fa][pos - 1] != 0) {
            dp[cur][pos] = dp[fa][pos - 1] * C[n - (pos - 1) - siz[cur]][siz[fa] - 1 - siz[cur]] % Mod * num % Mod;
        }
        (dp[cur][pos] += dp[cur][pos - 1]) %= Mod;
    }
    for (auto &to : g[cur]) {
        dfs(to, cur, deep + 1);
    }
    return;
}

void solve()
{
    std::cin >> n;
    for (int i = 2; i <= n; i++) {
        int fa = 0;
        std::cin >> fa;
        g[fa].push_back(i);
    }
    // 组合数 && 阶乘
    fac[0] = 1, C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = (fac[i - 1] * i) % Mod;
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod;
        }
    }
    init(1);
    dp[1][1] = 1;
    for (auto &to : g[1]) {
        dfs(to, 1, 2);
    }

    for (int i = 1; i <= n; i++) {
        std::cout << dp[i][i] * C[n - i][siz[i] - 1] % Mod * cnt[i] % Mod << " \n"[i == n];
    }

    return;
}
```
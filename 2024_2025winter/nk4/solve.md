## A

**题目大意**

有一个大小为 $n$ 的数组 $A$，$A_i \in [l_i, r_i]$，定义 $f(A) = \sum_{i = 1}^{n - 1}|A_i - A_{i + 1}|$。求 $f(A)$ 的期望。

**解题思路**

很明显这题主要就是要我们求相邻两个数之间差的绝对值的期望。这个期望也就是在两个区间里分别选一个数，这两个数之间的距离的期望。

不管这两个区间的位置关系如何，期望的分母都是好求的，即两段区间长度的乘积，现在最关键的地方就是求分子。

再考虑位置关系，如果两个区间有重合的部分，比如 $[2, 7]$ 和 $[4, 10]$，我们分成这么及部分计算：
1. $[2,3][4,10]$
2. $[4,7][8,10]$
3. $[4,7][4,7]$

即把部分相交的区间分成完全不相交和完全相同的区间来算，于是我们只用考虑这两种情况怎么计算分子。

对于完全相同的两区间，设区间的长度为 $n$，选择的两个数的距离为 $d$，则可以发现：
- $d = 0$，有 $n$ 种情况。
- $d = 1$，有 $2 * (n - 1)$ 种情况。
- $d = 2$，有 $2 * (n - 2)$ 种情况。
- $d = i$，有 $2 * (n - i)$ 种情况。

于是这种情况下的分子就是 $\sum_{i = 0}^{n - 1}2i(n - i)$，化简一下就好了。

对于完全不相交的两个区间$[l1,r1]$ 和 $[l2,r2]$（$r1 < l2$），很容易就看出两个数之间距离的最值 $mx = r2 - l1$ 和 $mn= l2 - r1$，而且只有一种情况会出现最值。距离从最值开始往中间靠，我们发现情况数是在以公差 1 增加的，而且当距离在 $r2 - r1$ 和 $l2 - l1$ 之间时，情况数总是为 $min(r1 - l1 + 1, r2 - l2 + 1)$。根据以上观察我们分两部算分子：中间情况数不变的部分和剩下的两边。公式化简后就是 $\frac{(r2 + l2 - r1 - l1) \times (r1 - l1 + 1) \times (r2 - l2 + 1)}{2}$。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
i64 inv(i64 a, i64 p = Mod - 2) {
    i64 res = 1;
    for (p; p; p >>= 1, a = a * a % Mod) {
        if (p & 1) {
            res = res * a % Mod;
        }
    }
    return res;
}

i64 cnt1(int l1, int r1, int l2, int r2) {
    // std::cout << l1 << ' ' << r1 << '\t' << l2 << ' ' << r2 << '\n';
    if (r1 < l1 || r2 < l2) {
        return 0;
    }
    return 1ll * abs(l2 + r2 - l1 - r1) * (r1 - l1 + 1) % Mod * (r2 - l2 + 1) % Mod * inv(2) % Mod;
}

i64 cnt2(int l, int r) {
    // std::cout << l << ' ' << r << '\n';
    if (r < l) {
        return 0;
    }
    int n = r - l + 1;
    return 1ll * n * (n - 1) % Mod * (n + 1) % Mod * inv(3) % Mod;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    int l1 = 0, r1 = 0;
    std::cin >> l1 >> r1;
    i64 ans = 0;
    for (int i = 0, l2 = 0, r2 = 0; i < n - 1; i++, l1 = l2, r1 = r2) {
        std::cin >> l2 >> r2;
        int l3 = std::max(l1, l2);
        int r3 = std::min(r1, r2);
        
        i64 son = 0;
        if (l3 > r3) {
            son = cnt1(l1, r1, l2, r2);
        }
        else {
            son = cnt1(std::min(l1, l2), l3 - 1, l3, l1 < l2 ? r2 : r1);
            son += cnt1(l3, r3, r3 + 1, std::max(r1, r2)) + cnt2(l3, r3);
            son %= Mod;
        }
        (ans += son * inv(1ll * (r1 - l1 + 1) * (r2 - l2 + 1) % Mod)) %= Mod;
    }
    std::cout << ans << '\n';
}
```
</details>

## BC
（B 题直接暴力枚举也可以，直接用C的做法也可以，就不单独拿出来了）

**题目大意**

定义一个 01 串平衡当且仅当串中 `01` 的数量等于 `10` 的数量。定义一个 $01$ 串的价值为 $i$ 的数量，$i$ 满足反转 01 串的第 $i$ 位后串是平衡的。现在给出的 01 串中有若干位置是未知的，计算所有可能的串的价值和。

**解题思路**

本题最重要的观察就是一个串平衡等价于串首等于串尾。  
可以这样考虑，将一个 01 串中所有连续的并成一个，这样整个 01 串就变成 0 和 1 交替出现的 01 串，当这个串的串首等于串尾时串平衡。

所以当 01 串两端的数是相同时，中间的数可以随意变化，否则只能变化两端。

具体细节见代码。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
i64 qpow(i64 a, i64 p) {
    i64 res = 1;
    for (p; p; p >>= 1, a = a * a % Mod) {
        if (p & 1) {
            (res *= a) %= Mod;
        }
    }
    return res;
}

void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    int tot = 0;
    for (auto &c : s) {
        if (c == '?') {
            tot++;
        }
    }

    i64 ans = 0;
    if (s[0] == '?' || s.back() == '?') {
        if (n == 1) {
            ans = 2;
        }
        else {
            ans = n * qpow(2, tot - 1) % Mod;
        }
    }
    else if (s[0] == s.back()) {
        if (n == 1) {
            ans = 1;
        }
        else {
            ans = (n - 2) * qpow(2, tot) % Mod;
        }
    }
    else {
        ans = 2 * qpow(2, tot) % Mod;
    }

    std::cout << ans << '\n';
}
```
</details>

## D

**题目大意**

给定两个字符串，可以随意打乱字符串和替换字符串中的字母，问至少替换多少次能使得两串拼接后是回文的。

**解题思路**

主要是尽量用原本就有的，具体看代码看注释吧。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
void solve()
{
    int n = 0, m = 0;
    std::string a, b;
    std::cin >> n >> m >> a >> b;
    if (a.length() < b.length()) {
        std::swap(a, b);
        std::swap(n, m);
    }

    std::vector<int> cnta(26, 0), cntb(26, 0);
    for (auto &c : a) {
        cnta[c - 'a']++;
    }
    for (auto &c : b) {
        cntb[c - 'a']++;
    }

    int cen = a.length() - b.length(); // 中心
    int len = n - cen; // 两侧
    for (int i = 0; i < 26; i++) {
        // 有相同的就放回文串两侧
        if (cnta[i] > cntb[i]) {
            len -= cntb[i];
            cnta[i] -= cntb[i];
            cntb[i] = 0;
        }
        else {
            len -= cnta[i];
            cntb[i] -= cnta[i];
            cnta[i] = 0;
        }
    }

    for (int i = 0; i < 26 && cen >= 2; i++) {
        // 成对的字母可以放在中心得两侧
        while (cen >= 2 && cnta[i] >= 2) {
            cen -= 2;
            cnta[i] -= 2;
        }
    }

    std::cout << len + cen / 2 << '\n';
}
```
</details>

## E

**题目大意**

在矩阵中选择一个点 $(x, y)$，然后可以获得的值是过该点且斜率分别为 1 和 -1 的两条直线上的点的值（交点只能取一次）。

问可获得的最大值。

**解题思路**

直接把所有可能出现的直线上的点权和算出来然后算一遍每个点取最大值就好了。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
constexpr int N = 1e3, M = 1e3, Inf = 1e9;
int g[N][M];
void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::map<int, i64> add, sub;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> g[i][j];
            add[i + j] += g[i][j];
            sub[i - j] += g[i][j];
        }
    }

    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans = std::max(ans, add[i + j] + sub[i - j] - g[i][j]);
        }
    }
    std::cout << ans << '\n';
    return;
}
```
</details>

## F

**题目大意**

数组 $A$ 中，定义点对 $<i, j>$（$i < j$）的值为 $(A_i + A_j) \% p$，问前 $k$ 大的值分别是多少。

**解题思路**

显然可以对所有数取模之后排序。然后需要观察到一点：$A_i + A_j$ 的值可能小于 $p$ 也可能大于等于 $p$，而且在模 $p$ 后前者的值一定是大于后者的。于是对于 $i$ 我们可以把 $j$ 分成两类：一类是使 $A_i + A_j < p$ 的；一类是使 $A_i + A_j > p$ 的。并且在两类中，点对的值都随着 $A_j$ 的增大而增大。于是对于每一个 $i$，我们可以能够找到 $j$ 使得点对的值由最大到最小。具体用一个优先队列维护每一个 $i$ 目前能取得的最大值然后每次取最大就好了。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
struct R {
    int l, r;
    int idx;
    int val;

    bool operator< (const R &u) const {
        return val < u.val;
    }
};

void solve()
{
    int n = 0, p = 0, k = 0;
    std::cin >> n >> p >> k;
    std::vector a(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i] %= p;
    }
    std::sort(a.begin(), a.end());
    
    std::priority_queue<R> q;
    for (int l = 0; l < n - 1; l++) {
        int r = std::lower_bound(a.begin(), a.end(), p - a[l]) - a.begin() - 1;
        r = r <= l ? n - 1 : r;
        q.push(R({ l, r, r, (a[l] + a[r]) % p }));
    }
    
    while (k--) {
        if (q.empty()) {
            std::cout << "-1 ";
        }
        else {
            R t = q.top();
            q.pop();
            std::cout << t.val << ' ';
            t.r = t.r - 1 == t.l ? n - 1 : t.r - 1;
            if (t.r != t.idx) {
                t.val = (a[t.l] + a[t.r]) % p;
                q.push(t);
            }
        }
    }
    std::cout << '\n';
}
```
</details>

## I

略

## J

**题目大意**

在一张不一定连通的无向图中，我们有两种方式访问节点：
1. 可以使用传送从任意位置访问到任意节点
2. 从一个已经被访问过的节点出发，可以访问与它相邻的任意节点。

传送次数有限，但至少为 1（因为一开始一个节点都没访问，只能通过传送访问节点）。问最多能访问到多少个节点，并在访问节点数最多的前提下输出一种字典序最小的访问顺序。

**解题思路**

首先从节点最小的编号开始搜索连通块，并记录下每个连通块的大，并用连通块里的最小编号作为该连通块的编号。

因为首先要保证访问到的节点最多，其次保证字典序最小，所以我们对记录下的连通块，以大小为第一关键字编号为第二关键字排序，并且优先将传送次数用于传送到未被访问过的连通块。

至于找到字典序最小的访问顺序，我们可以用优先队列实现的 bfs：首先将所有需要访问的连通块的编号入队（其实就是连通块中编号最小的节点），再每次弹出最小的并将它周围围被访问过的节点入队。

但是注意了，如果我们的传送次数足够多，即在保证可以到达所有的连通快后还有剩余的传送次数，在 bfs 的过程中如果我们发现在队列中的编号最小的节点不是剩下还没访问节点中最小的节点，我们就可以直接传送到那里去。而且这种情况出现的话说明我们一定可以访问到所有节点，而且在传送次数用完之前我们一定可以按照 1 2 3 4 5……的顺序访问节点。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
constexpr int N = 2e5, M = 5e5, Inf = 1e9;
std::vector<int> g[N + 5], col(N + 5);
std::vector<std::pair<int, int>> reg; // 区域的大小和最小的编号
bool vis[N + 5]; // dfs
bool inq[N + 5];

void dfs(int cur, int c, int &cnt) {
    col[cur] = c, cnt++;
    for (auto &to : g[cur]) {
        if (col[to] == 0) {
            dfs (to, c, cnt);
        }
    }
}

void solve()
{
    int n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;

    reg.clear();
    for (int i = 1; i <= n; i++) {
        inq[i] = false;
        g[i].clear();
        col[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }


    for (int i = 1; i <= n; i++) {
        if (col[i] == 0) {
            int cnt = 0;
            dfs(i, i, cnt);
            reg.push_back({ cnt, i });
        }
    }

    std::sort(reg.begin(), reg.end(), [&](const auto &u, const auto &v) {
        if (u.first == v.first) {
            return u.second < v.second;
        }
        else {
            return u.first > v.first;
        }
    });
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    int ans = 0;
    for (int i = 0; i < std::min(k, int(reg.size())); i++) {
        ans += reg[i].first;
        q.push(reg[i].second);
        inq[reg[i].second] = true;
    }
    k -= reg.size();
    std::vector<int> node(n, 0);
    for (int i = 0; i < n; i++) {
        node[i] = i + 1;
    }
    auto it = node.begin();
    
    std::cout << ans << '\n';
    while (not q.empty()) {
        int cur = 0;
        if (k > 0) { // 还能传送时
            cur = *it; // 肯定能到达 *it
            if (not inq[*it]) { // 不在队列里就传送
                inq[*it] = true;
                k--;
            }
            else { // 在队列里的话就一定是堆顶
                q.pop();
            }
            it++;
        }
        else { // 没有传送次数就正常取
            cur = q.top();
            q.pop();
        }
        std::cout << cur << ' ';

        for (auto &to : g[cur]) {
            if (not inq[to]) {
                q.push(to);
                inq[to] = true;
            }
        }
    }
    std::cout << '\n';
    return;
}
```
</details>


## K

略

## L

**题目大意**

对于两个大小为 $n$ 的数组 $A$ 和 $B$，每次询问给出 $l$ 和 $r$，计算：$\sum_{i = l}^{r}\sum_{j = i}^{r}A_i\oplus B_j$

**解题思路**

假设我们有一个 $n\times n$ 的矩阵，矩阵第 $i$ 行 $j$ 列的值就是 $A_i \oplus B_i$，于是问题就变成了在这个矩形里计算一块三角形区域的和。

首先想到对于异或的求和，我们都可以一位一位地来计算贡献，于是下文我们只考虑第 $k$ 位对答案的贡献，其他位的贡献都是同理的。

即使只用考虑一位，计算该位在任意一个三角形区域的贡献都是比较困难的。但是如果我们固定 $l = 1$，我们是有办法计算 $r$ 从 1 到 $n$ 的答案分别是多少的。先假设$A_{i,k}$表示 $A$ 中第 $i$ 个数的第 $k$ 位（$B$ 中同理）。如果知道了该位在 $[l, r-1]$ 上的贡献，那么 $[l, r]$ 上的贡献就是在前者的基础上加上 $(\sum_{i = l}^{r}B_{r,k}\oplus A_{i,k}) << k$，也就是计算 $A_{i,k}$ 有多少跟 $B_{r,k}$ 的异或和是 1，然后再位移一下。于是只要我们能快速计算 $k$ 位上 $i \in[l, r]$ 的区间里，$A_{i,k}$ 为 1 的数量就可以快速计算贡献。(前缀和就好了)

在知道了第 $k$ 位在每一个 $[1, r]$ 上对答案的贡献后我们就可以这样来计算第 $k$ 位在任意区间 $[l, r]$ 的贡献：$[1, r]$ 上的贡献 - $[1, l - 1]$ 上的贡献 - 一个矩形的贡献。而且该位上这个矩形的贡献具体是：$(\sum_{i = 1}^{l - 1}\sum_{j = l}^{r}A_{i,k}\oplus B_{j,k}) << k$（怎么来的？画画图就清晰明了了）。由于是矩形，我们可以直接这样算：$\sum_{i = 1}^{l - 1} (A_{i,k} == 0) \times \sum_{j = l}^{r}(B_{j,k} == 1) + \sum_{i = 1}^{l - 1} (A_{i,k} == 1) \times \sum_{j = l}^{r}(B_{j,k} == 0)$。在该位上维护一个前缀和方便计算区间内 1 的数量就好了。

**CODE**

（以下代码是赛时写的，整体思路是以上，但比较史，而且是用树状数组而不是前缀和。）

<details>
<summary>点击查看代码</summary>

```cpp
class BIT {
private:
    int n;
    std::vector<int> a;

    int lowbit(int x) {
        return x & -x;
    }
    
    int sum(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= lowbit(i)) {
            res += a[i];
        }
        return res;
    }
public:
    BIT(int _n) {
        n = _n;
        a.assign(n + 1, 0);
    }

    void add(int pos, int val) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            a[i] += val;
        }
    }

    int sum(int l, int r) {
        if (l > r) {
            return 0;
        }
        return sum(r) - sum(l - 1);
    }
};

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    
    std::vector v(n + 1, 0);
    std::vector a(L, BIT(n));
    std::vector b(L, BIT(n));
    for (int i = 1; i <= n; i++) {
        int x = 0;
        std::cin >> x;
        for (int bit = 0; bit < L; bit++) {
            if ((x >> bit) & 1) {
                b[bit].add(i, 1);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> v[i];
        for (int bit = 0; bit < L; bit++) {
            if ((v[i] >> bit) & 1) {
                a[bit].add(i, 1);
            }
        }
    }

    std::vector pre(n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1];
        for (int bit = 0; bit < L; bit++) {
            i64 d = 0;
            i64 cntone = b[bit].sum(1, i);
            if ((v[i] >> bit) & 1) {
                d = ((i - cntone) << bit) % Mod;
            }
            else {
                d = (cntone << bit) % Mod;
            }
            (pre[i] += d) %= Mod;
        }
    }

    while (q--) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        i64 ans = (pre[r] + Mod - pre[l - 1]) % Mod;
        i64 d = 0;

        if (l != 1) {
            i64 w = r - l + 1, h = l - 1;
            for (int bit = 0; bit < L; bit++) {
                i64 acnt1 = a[bit].sum(l, r), acnt0 = w - acnt1;
                i64 bcnt1 = b[bit].sum(1, h), bcnt0 = h - bcnt1;
                (d += ((acnt1 * bcnt0 + acnt0 * bcnt1) << bit) % Mod) %= Mod;
            }
        }

        (ans += Mod - d) %= Mod;
        std::cout << ans << '\n';
    }

    return;
}
```
</details>

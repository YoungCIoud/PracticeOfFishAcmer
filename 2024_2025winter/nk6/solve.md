## A

栈秒了

<details>
<summary>CODE</summary>

```cpp
void solve()
{
    int n = 0;
    std::cin >> n;
    std::stack<int> a;
    for (int i = 0; i < n; i++) {
        int x = 0;
        std::cin >> x;
        if (a.empty() || a.top() != x) {
            a.push(x);
        }
    }
    std::cout << a.size() << '\n';
}
```
</details>

## B

**题目大意**

给定两个序列 $A$ 和 $B$，可以进行以下操作：
- 花费代价 $c1$ 同时删去 $A_i$ 和 $B_i$。
- 花费代价 $c2$ 交换 $A_i$ 和 $B_i$。

问需要花费多少代价，才能使两个序列同时是不降的。

$N < 10^3$


**解题思路**

注意到数据量不大，所以可以用 $O(n^2)$ 的算法。

设 $dp_{i,0/1}$ 表示两个序列中前 $i$ 个数都不降且第 $i$ 对数交换/不交换所花费的最小代价。且令 $dp_{0,0/1} = 0$。  
假设 $0 \leq j < i$ 且 $a[j] \leq a[i], b[j] \leq b[i]$， $0 \leq k < i$ 且 $a[k] \leq b[i], b[k] \leq a[i]$，则我们可以这样转移：  
$dp_{i,0} = min(dp_{j,0} + (i - j - 1) \times c1, dp_{k,1} + (i - k - 1) \times c1)$  
$dp_{i,1} = min(dp_{j,1} + (i - j - 1) \times c1 + c2, dp_{k,0} + (i - k - 1) \times c1 + c2)$。

于是我们就得到了一个 $O(n^2)$ 的 dp，特别的，我们可以在两个序列后插入第 $n + 1$ 个数 $Inf$，这样最后直接输出 $dp_{n + 1, 0}$ 就好了。

<details>
<summary>CODE</summary>

```cpp
void solve()
{
    int n = 0, c1 = 0, c2 = 0;
    std::cin >> n >> c1 >> c2;
    std::vector a(n + 1, 0ll), b(n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i] >> b[i];
    }
    a.push_back(Inf), b.push_back(Inf);
    // dp[i][0/1] 前 i 条记录不变第 i 条 / 反转第 i 条 所需要的最小代价
    std::vector dp(n + 2, std::vector(2, Inf));
    dp[0] = { 0, 0 };
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] <= a[i] && b[j] <= b[i]) {
                dp[i][0] = std::min(dp[i][0], dp[j][0] + 1ll * (i - j - 1) * c1);
                dp[i][1] = std::min(dp[i][1], dp[j][1] + 1ll * (i - j - 1) * c1 + c2);
            }
            if (a[j] <= b[i] && b[j] <= a[i]) {
                dp[i][1] = std::min(dp[i][1], dp[j][0] + 1ll * (i - j - 1) * c1 + c2);
                dp[i][0] = std::min(dp[i][0], dp[j][1] + 1ll * (i - j - 1) * c1);
            }
        }
    }
    std::cout << dp[n + 1][0] << '\n';
}
```
</details>

## C

**题目大意**

序列 $A$ 中有无数个数，且 $A_i = 2i - 2$。求出所有长度大于 1 的连续子序列的和，对这些和从大到小排序并做 **去重** 后得到以个新的序列，输出这个序列的第 $k$ 个数。

$k < 10^{18}$

**解题思路**

打表后可以发现序列是在所有的偶数中，除去除了 2 以外的 2 的次幂得到的序列。知道这点后就能做了。

<details>
<summary>CODE</summary>

```cpp
void solve()
{
    i64 k = 0;
    std::cin >> k;
    k--;
    if (k == 0) {
        std::cout << 2 << '\n';
        return;
    }

    int l = 1, r = 62;
    while (l <= r) {
        int m = l + r >> 1;
        if ((1ull << m) < k + m + 1ll) {
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }
    // std::cout << r << ' ' << l << '\n';
    k -= (1ull << r) - r - 1;
    std::cout << (1ull << l) + (k << 1) << '\n';
}
```
</details>

## F

**题目大意**

有 $n$ 个二元组 $<a_i, b_i>$，可以按照任意顺序选择二元组。初始时拥有的价值 $val$ 为 0，选择一个二元组后可以更新价值。具体的，选择任意一个二元组 $<a_i, b_i>$ 后，如果你目前拥有的价值小于 $a_i$，那你拥有的价值变成 $max(val, a_i)$，否则变成 $max(val, a_i + b_i)$。每个二元组只能选择一次，问最后能取得的最大价值是多少。

**解题思路**

直接排序，和小的放前面。我们从前往后遍历更新目前拥有的价值 $val$，遍历到第 $i$ 个物品时，如果 $a_i \leq val$，则 $val$ 更新为 $a_i + b_i$，否则就是 $a_i > val$，由于 $val$ 已经是前 $i - 1$ 个二元组能取到的最大值，所以先取第 $i$ 个二元组的话，$val > a_{i - 1}$ 一定可以取得 $a_{i - 1} + b_{i - 1}$，此时 $val = max(a_{i - 1} + b_{i - 1}, a_i)$。

<details>
<summary>CODE</summary>

```cpp
void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n, std::array<int, 2>{ 0, 0 });
    for (auto &[x, y] : a) {
        std::cin >> x >> y;
    }
    std::sort(a.begin(), a.end(), [&](auto &u, auto &v) {
        if (u[0] + u[1] == v[0] + v[1]) {
            return u[0] < v[0];
        }
        else {
            return u[0] + u[1] < v[0] + v[1];
        }
    });

    int mx = a[0][0];
    for (int i = 1; i < n; i++) {
        if (mx >= a[i][0]) {
            mx = std::max(mx, a[i][0] + a[i][1]);
        }
        else {
            mx = std::max(mx, a[i][0]);
            mx = std::max(mx, a[i - 1][0] + a[i - 1][1]);
        }
    }

    std::cout << mx << '\n';
    return;
}
```
</details>

## H

**题目大意**

构造一个长度为 $n$ 的排列，这个序列满足 $m$ 个限制条件 $l_i,r_i,c_i$，表示对区间 $[l_i,r_i]$ 从小到大排序后，原本第 $c_i$ 个数的位置会变。同时保证所有区间的长度奇偶性相同。

**解题思路**

当所有区间的长度都是偶数时，直接输出字典序最大的排列就好了。此时对任意一个区间进行排序区间内所有的数的位置都会改变。

当区间长度都是奇数时，上述构造方法就不成立，因为区间最中间一个数的位置不会变。  
考虑最小的三个数的区间，此时只有两种构造方法：大小中（`312`）和中大小（`231`）。于是我们只用所有的长度为 3 的区间满足两种构造方法只易就好了。如果用图来表示构造出来的序列，形状应该是下降的折线。比如：
- 长度为 4 的排列： `4231`
- 长度为 5 的排列： `53412`
- 长度为 6 的排列： `645231`
- 长度为 7 的排列： `7563412`

<details>
<summary>CODE</summary>

```cpp
void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector s(m, std::array<int, 3>{});
    
    for (auto &[l, r, c] : s) {
        std::cin >> l >> r >> c;
    }
    if ((s[0][1] - s[0][0]) % 2 == 1) {
        for (int i = n; i >= 1; i--) {
            std::cout << i << " \n"[i == 1];
        }
    }
    else {
        std::cout << n << ' ';
        for (int i = n - 1; i >= 2; i -= 2) {
            std::cout << i - 1 << ' ' << i << ' ';
        }
        if (n % 2 == 0) {
            std::cout << 1 << ' ';
        }
        std::cout << '\n';
    }
    return;
}
```
</details>

## I

**题目大意**

给定一个排列，有个形如 $l_i, r_i, c_i$ 的询问，表示对区间 $[l_i, r_i]$ 中的数从小到大排序后，原本位于 $c_i$ 的数到哪里去了。

**解题思路**

想要知道对一个区间内的数排序后某一个数的位置，我们只需要知道区间里有多少个数是小于它的就好了。于是我们将询问排序，位置 $c_i$ 上的数小的询问在前面，从 1 开始往后遍历，于是每次只用查询区间内有多少个已查询的数，查询完后再把 $c_i$ 标记已查询即可。

<details>
<summary>CODE</summary>

```cpp
class BIT {
private:
    int n;
    std::vector<int> tr;

    int lowbit(int x) {
        return x & -x;
    }
    int sum(int pos) {
        int res = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            res += tr[i];
        }
        return res;
    }
public:
    BIT(int _n) {
        n = _n;
        tr.assign(n + 1, 0);
    }

    void add(int pos) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            tr[i]++;
        }
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector p(n + 1, 0), pos(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> p[i];
        pos[p[i]] = i;
    }

    std::vector q(n + 1, std::vector<std::array<int, 3>>());
    for (int i = 0; i < m; i++) {
        int l = 0, r = 0, c = 0;
        std::cin >> l >> r >> c;
        q[p[c]].push_back({ i, l, r });
    }
    
    std::vector ans(m, 0);
    std::vector vis(n + 1, false);
    BIT t(n);
    for (int i = 1; i <= n; i++) {
        for (auto &[id, l, r] : q[i]) {
            ans[id] = l + t.sum(l, r);
        }
        t.add(pos[i]);
    }
    for (auto &i : ans) {
        std::cout << i << '\n';
    }
    return;
}
```
</details>

## J

**题目大意**

$n$ 轮游戏，每轮游戏可以进行两次操作（只选一个也可以）：
- 攻击力增 1
- 以当前攻击力攻击，并造成等同于当前攻击力的伤害。攻击后减少一点攻击力，攻击力为 0 时不能攻击。

你的初始攻击力是 $x$，且操作 $1$ 至多使用 $y$ 次，问最多造成多少点伤害。

**解题思路**

首先肯定是要尽量把 $y$ 用完的。而且用 $y$ 还得在一开始几轮。

在攻击力降为 0 之前有三个阶段
1. 只增加攻击力不攻击
2. 即增加攻击力又攻击
3. 只攻击

在 $n$ 轮游戏中，这三个阶段不一定都全部存在，但是如果存在一定是按顺序来的。而且阶段 3 只会在 $y$ 次操作 1 用完后才会进行。于是我们只用考虑如何分配阶段 1 和阶段 2。由于数据范围很小，直接枚举每种分配方案取最大值就好了。

<details>
<summary>CODE</summary>

```cpp
void solve()
{
    int n = 0, x = 0, y = 0;
    std::cin >> n >> x >> y;
    int ans = 0;
    // 枚举前面只磨刀的轮数
    for (int i = 0; i <= std::min(n, y); i++) {
        int d0 = x + i; // 初始伤害
        int con = std::min(n, y) - i; // 边磨刀边攻击的轮数
        int att = std::min(n - con - i, d0); // 只攻击的轮数
        ans = std::max(ans, (d0 + 1) * con + (2 * d0 - att + 1) * att / 2);
    }
    std::cout << ans << '\n';
    return;
}
```
</details>

## K

判断 $2x+1$ 是否跟 $y$ 模 4 同余就好了。

<details>
<summary>CODE</summary>

```cpp
void solve()
{
    int x = 0, y = 0;
    std::cin >> x >> y;
    x += x + 1;
    if (y == 0 || (x + y) % 2 == 0) {
        std::cout << "YES\n";
    }
    else {
        std::cout << "NO\n";
    }
}
```
</details>

## L

首先看能不能从原串中选出一个子序列使得子序列组成的串等于目标串，有的话就剔除找的的子序列，然后统计剩余的串中各个字母分别出现了多少次。如果出现次数最多的字母出现的次数超过了一半，直接判无解，否则只有当剩余串的串长是偶数是才判有解。

<details>
<summary>CODE</summary>

```cpp
bool solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    std::vector cnt(26, 0);
    int p = 0;
    for (auto &c : s) {
        cnt[c - 'A']++;
        if (p < T.size() && c == T[p]) {
            p++;
        }
    }
    
    if (p != T.size()) {
        return false;
    }
    
    for (auto &c : T) {
        cnt[c - 'A']--;
    }
    std::sort(cnt.begin(), cnt.end());
    n -= T.size();
    if (cnt.back() * 2 > n) {
        return false;
    }
    else {
        return n % 2 == 0;
    }
}
```
</details>
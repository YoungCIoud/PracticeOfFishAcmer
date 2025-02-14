## A

手玩秒了：
奇数yes偶数no

## B

**题目大意**

$n$ 个小球组成一个环，每个小球上都写有一个数字。对于一个小球，我们可以拿掉它当且仅当满足下面两个条件之一：
- 只剩这一个小球
- 这个小球的数和顺时针方向上的下一个小球的数之和是个质数

问是否存在一种拿球的顺序使得最终能够拿掉所有的球，有还需要输出顺序。

**解题思路**

若 $n$ 个小球排成一条线而不是组成一个环，我们可以贪心的去解决这个问题：只要和是质数就拿（用栈实现）。这线上这个贪心正确的原因是，前面的球不管是否拿下，都不影响后面的球是否能被拿下，也就是说**无后效性**。但显然在环上这个贪心是错的。

在环上我们就在环上的 $n$ 条长度为 $n$ 的链上去找一个解，当然不用每一条链都去找单独找一遍。具体的，对于第一条链我们老老实实按找栈的思路去拿，如果最后只剩下一个，那就是有解直接退出就好了，否则对于第二条链，先检查当前的栈底，如果是第一条链上的第 1 个数，那就将这个数弹出去（因为在这第二条链上这个数应该在最后面去了），实际上这时候我们就不是用栈来实现，而是 deque。此后都这样找，找不到就说明无解。

以上做法涉及到环形 dp 的一个定理：
> 在无后效性的前提下，任何一个环上的 dp 转移关系，一定等价于考虑所有以 $i$ 为起点的 $n$ 条链上 dp 转移关系的并集。

**CODE**

<details>
<summary>点击查看代码</summary>

```
bool vis[M + 5];

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
    }

    int idx = -1;
    std::deque<int> q;
    for (int i = 0, j = 0; i < n && idx == -1; i++) {
        while (j - i < n) {
            while (not q.empty() && not vis[a[q.back() % n] + a[j % n]]) {
                q.pop_back();
            }
            q.push_back(j);
            j++;
        }
        while (not q.empty() && q.front() < i) {
            q.pop_front();
        }

        if (q.size() == 1) {
            idx = i;
        }
    }

    if (~idx) {
        std::cout << "Yes\n";
        int r = idx;
        std::stack<int> stk;
        while (r - idx < n) {
            while (not stk.empty() && not vis[a[stk.top() % n] + a[r % n]]) {
                std::cout << stk.top() % n << ' ';
                stk.pop();
            }
            stk.push(r);
            r++;
        }
        std::cout << stk.top() % n << '\n';
    }
    else {
        std::cout << "No\n";
    }

    return;
}

int main()
{
    std::vector<int> pri;
    for (int i = 2; i <= M; i++) {
        if (not vis[i]) {
            pri.push_back(i);
        }
        for (auto &p : pri) {
            if (p * i > M) {
                break;
            }
            vis[p * i] = true;
            if (i % p == 0) {
                break;
            }
        }
    }

    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
```
</details>

## C

**题目大意**

有一单词表，上面有 $n$ 个由小写字母组成的单词，现在需要通过 26 个字母键和一个退格键在记事本上敲出这些单词。敲击一次字母或退格键都算敲击一次。注意，如果你在记事本上敲出了 `abcd` ，这不代表你敲出了 `bcd` ，当且仅当记事本上是 `bcd` 才算。问至少需要敲击多少下才能敲出所有单词。

**解题思路**

在建立了字典树后，题目的描述就可以这样理解：
- 敲击字母就往叶子的方向走
- 退格就是往回走

于是最少的敲击数就是：字典树的节点数 $\times$ 2 - 最长的单词的长度。乘 2 是考虑了退格，最后的减是因为最后一个单词我们不用退格了。

**CODE**

<details>
<summary>点击查看代码</summary>

```
constexpr int N = 1e5, M = 1e6, Inf = 1e9;
int tr[M + 1][26], tot;

void insert(std::string s) {
    int cur = 0;
    for (auto &c : s) {
        if (tr[cur][c - 'a'] == 0) {
            tr[cur][c - 'a'] = ++tot;
        }
        cur = tr[cur][c - 'a'];
    }
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        mx = std::max(mx, int(s.length()));
        insert(s);
    }
    int l = 0, r = 0;
    std::cin >> l >> r;
    std::cout << tot * 2 - mx << '\n';
}
```
</details>

## D

**题目大意**

题目背景同上一题，不同的地方在于，上一题要求敲出全部的 $n$ 个单词，而这一题有 $q$ 组询问，每次独立地要求敲出 $[l_i, r_i]$ 之间的单词，问每次询问至少要敲击多少次。

**解题思路**

上一题的答案是：字典树的节点数 $\times$ 2 - 最长的单词的长度，这一题因为有了范围限制，就变成了：范围内的单词组建的字典树的节点数 $\times$ 2 - 范围内最长的单词的长度。对于后者，就是维护区间最大值，而对于前者，我们当然不能每次都重新建树，需要另外找办法。

如果我们在建树插入单词的过程中给树上的节点上色（对已经上过色的节点进行覆盖），那么统计字典树的节点数就变成了统计不同颜色的节点数之和。假设我们已经插入到了第 $r$ 个单词，那么我们能够查询到区间 $[i, r](0 < i < r)$ 里单词组成的字典树要多少个节点，具体的查询方法就是统计目前的字典树中，有多少节点的颜色是在区间 $[i, r](0 < i < r)$ 中。因为后插入的单词在上色过程中会覆盖掉已上色的节点，所以我们就只能查询后缀区间而不是任意区间。

统计颜色只需要一种支持单点修改和区间查询的数据结构就好了，比如树状数组。

**CODE**

<details>
<summary>点击查看代码</summary>

```
constexpr int N = 1e5, M = 1e5, L = 1e6, T = 100;

int tr[L + 5][27];
int tot = 0;

class BIT {
private:
    int n;
    std::vector<int> a;

    int lowbit(int x) {
        return x & -x;
    }

    int sum(int pos) {
        int res = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
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
        return sum(r) - sum(l - 1);
    }
};

void insert(std::string s, int id, BIT &cnt) {
    int cur = 0;
    for (auto &c : s) {
        int to = c - 'a';
        if (tr[cur][to] == 0) {
            tr[cur][to] = ++tot;
        }
        else {
           cnt.add(tr[tr[cur][to]][26], -1);
        }
        cur = tr[cur][to];
        tr[cur][26] = id;
    }
    cnt.add(id, s.length());
}

int main () {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector s(n + 1, std::string{});
    std::vector ans(m, 0);
    BIT cnt(n);
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
    }
    std::vector q(n + 1, std::vector<std::array<int, 2>>{});
    for (int i = 0; i < m; i++) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        q[r].push_back({ l, i });
    }

    std::pair<int, int> stk[n];
    int top = 0;
    for (int r = 1; r <= n; r++) {
        insert(s[r], r, cnt);
        int len = s[r].length();
        while (top && stk[top - 1].second <= len) {
            top--;
        }
        stk[top++] = { r, len };
        for (auto &[l, id] : q[r]) {
            ans[id] = (cnt.sum(l, r)) * 2 - (*std::lower_bound(stk, stk + top, std::make_pair(l, 0))).second;
        }
    }

    for (auto &i : ans) {
        std::cout << i << '\n';
    }

    return 0;
}
```
</details>

## E

**题目大意**

在数轴上有若干不计体积质量相同的小球，每个小球的初始位置不同且速率都为每秒一个单位，速度的方向为数轴的正方向或者反方向。且小球之间的碰撞都为完全弹性碰撞（即在质量相同的情况下碰撞后发生速度交换）。问发生 $k$ 次碰撞至少要多少秒。

**解题思路**

首先利用相对的思想，我们可以认为所有速度方向为正的都静止，而反方向的就以每秒两个单位运动。这样我们就可以很容易的二分时间长度来找到答案了。为了在二分的时候不涉及小数，对于当前正在二分的 $mid$ 我们可以认为它的含义是 $mid$ 个 0.5s，这样做后相对速度就要看成每 0.5 秒一个单位。具体的 `chk` 函数就是对于每个速度方向为正的小球，算它前面 $mid$ 个单位内有多少个反方向的小球。

注意最后二分出来的答案还要除二。

**CODE**

<details>
<summary>点击查看代码</summary>

```
void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector<int> a, b;
    for (int i = 0; i < n; i++) {
        int p = 0, v = 0;
        std::cin >> p >> v;
        if (~v) {
            a.push_back(p);
        }
        else {
            b.push_back(p);
        }
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    // 0.5s 的数量
    int l = 0, r = Inf;
    while (l <= r) {
        int m = l + r >> 1;

        int num = 0;
        for (auto &p : a) {
            num += std::upper_bound(b.begin(), b.end(), p + m) - std::upper_bound(b.begin(), b.end(), p);
        }

        if (num >= k) {
            r = m - 1;
        }
        else {
            l = m + 1;
        }
    }
    
    if (r == Inf) {
        std::cout << "No\n";
    }
    else {
        std::cout << "Yes\n";
        double ans = l;
        ans /= 2.0;
        std::cout << std::fixed << std::setprecision(6) << ans << '\n';
    }
}
```
</details>

## F

略

## G

**题目大意**

有一个长度为 $n$ 的序列 $A$，其中 $A_i = n\mod i$，问这个序列前 $k$ 大的数之和为多少。

$n \leq 10^9$

**解题思路**

当然不可能直接把整个序列求出来再排序。

通过打表找规律可以发现未排序的整个序列  $A$ 是由若干个等差数列组成。因为存在区间 $[l, r]$，使得区间里的 $i$ 满足 $c \times i + A_i = n$（在此区间中 $c$ 是一个固定的数），在此区间下可以得到  $A_i = -c * i + n$， 即一个等差序列。找出这些区间的过程就是**整除分块**的过程（$\lfloor \frac{n}{l}\rfloor = \lfloor \frac{n}{r}\rfloor$ = c）。

令 $num(i)$ 表示在序列 $A$ 中等于 $i$ 的数的个数，则在前 $k$ 大的数中，肯定存在一个数 $m$ 满足 $\sum_{i = m}^{n}num(i) \leq k$ 而 $k < \sum_{i = m - 1}^{n}num(i)$，也就是说大于等于 $m$ 的数都是前 $k$ 大的数，不是所有的 $m - 1$ 都在前 $k$ 大的数的范围之内。

于是我们就去二分 $m$ 然后看各个等差数列中大于等于 $m$ 的数的个数是否小于 $k$ 就好了。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
// 0 首项
// 1 公差
// 2 项数
using seq = std::array<int, 3>;

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;

    std::vector<seq> s;

    int mx = 0;
    for (int i = 1; i <= n; i++) {
        int f = n / i, j = n / f;
        mx = std::max(mx, n % i);
        s.push_back({ n % i, -f, j - i + 1 });
        i = j;
    }

    // for (auto &[x, y, z] : s) {
    //     std::cout << x << ' ' << y << ' ' << z << '\n';
    // }

    // 二分求一个数 x 使得大于等于 x 的数都可以选而 x - 1 只能尽可能多的选
    int l = 0, r = mx;
    while (l <= r) {
        int mid = l + r >> 1;

        int cnt = 0;
        for (auto &[a, d, m] : s) {
            if (mid <= a) {
                int num = std::min(m, (mid - a) / d + 1);
                cnt += num;
            }
        }

        if (cnt > k) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }

    i64 ans = 0;
    for (auto &[a, d, m] : s) {
        if (l <= a) {
            int num = std::min(m, (l - a) / d + 1);
            k -= num;
            int b = a + d * (num - 1);
            ans += 1ll * (a + b) * num / 2;
        }
    }
    ans += 1ll * k * r;
    std::cout << ans << '\n';

    return;
}
```
</details>

## H

**题目大意**

有一颗 $n$ 个节点的无根树，每棵树都有一个颜色（黑色或者白色）。定义一颗树的权值是树上所有起点为白色终点为黑色的路径的长度和。按顺序给出所有 $n - 1$ 条边，问对于所有的 $i \in [1, n - 1]$，删除第 $i$ 条边后分成的两颗树的权值分别是多少。

**解题思路**

要是只问给出的原始树的权值，我们就可以直接以任意一个点为根节点树形 dp。具体的我们需要在 dp 的过程中计算以下值:
- $dp_i$， 表示以 $i$ 为根的子树的权值
- $cnt_{i, 0(1)}$， 表示以 $i$ 为根的子树中，有多少路径是以 $i$ 为一个端点，另一个端点是白色（黑色）。
- $tot_{i, 0(1)}$ 表示以 $i$ 为根的子树中， 满足一个端点是 $i$ 而另一个端点是白色（黑色）的路径的总节点数（可以看成一个节点就对应一条边，这样好转移一些）。

于是对于节点 $u$ 和其子节点 $v$，有以下转移：

1. $dp_u = dp_u + dp_v$
2. $dp_u = dp_u + cnt_{u,0(1)} * tot_{v,1(0)}$
3. $dp_u = dp_u + cnt_{v,0(1)} * (tot_{u,1(0)} - cnt_{u,1(0)})$
4. $tot_{u,0(1)} = tot_{u,0(1)} + tot_{v,0(1)} + cnt_{v,0(1)}$
5. $cnt_{u,0(1)} = cnt_{u,0(1)} + cnt_{v,0(1)}$

特别要注意转移中的$+cnt$ 和 $-cnt$。

这样我们就计算出了一半的答案：对于边 $u - v$，我们计算出了在上述树形 dp 中为儿子一侧的答案，对于为父亲的一侧我们还没有的出。

在完成一次 dp 得出一半的答案后，就来到了本题最精妙的操作：父亲节点和儿子节点的倒置。观察到转移的几个式子是可逆的，即从 5 式开始将所有的 + 号变成 - 号（注意 2 式中的 - 号不用变），就可以撤销从子节点 $v$ 到父节点 $u$ 的转移。我们把转移看成连接两个节点，逆操作撤销就相当于断开了连接两个节点的边。经过一次逆操作，我们就的到了父节点一侧的答案。同时再把 $v$ 看做成父节点 $u$ 看作成子节点进行转移，就完成了父节点和子节点的倒置。用这种方法在进行一次树形 dp 就可以得到全部的答案。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
std::string col;
std::vector<int> g[N];
std::map<std::pair<int, int>, int> idx;
std::array<i64, 2> ans[N];

// 以 i 为一个端点另一端是黑（白）路径的数量
// 以 i 为一个端点另一端是黑（白）路径的总长度
std::array<i64, 2> cnt[N], tot[N];
i64 dp[N]; // 结果

// u 是 v 的父节点， 将 v 转移到 u。
void trans(int u, int v) {
    dp[u] += dp[v] + cnt[u][0] * tot[v][1] + cnt[u][1] * tot[v][0];
    dp[u] += cnt[v][0] * (tot[u][1] - cnt[u][1]) + cnt[v][1] * (tot[u][0] - cnt[u][0]);
    tot[u][0] += tot[v][0] + cnt[v][0];
    tot[u][1] += tot[v][1] + cnt[v][1];
    cnt[u][0] += cnt[v][0];
    cnt[u][1] += cnt[v][1];
}
// u 是 v 的父节点， 将 v 变成父亲
void inv(int u, int v, bool W) {
    tot[u][0] -= tot[v][0] + cnt[v][0];
    tot[u][1] -= tot[v][1] + cnt[v][1];
    cnt[u][0] -= cnt[v][0];
    cnt[u][1] -= cnt[v][1];
    dp[u] -= dp[v] + cnt[u][0] * tot[v][1] + cnt[u][1] * tot[v][0];
    dp[u] -= cnt[v][0] * (tot[u][1] - cnt[u][1]) + cnt[v][1] * (tot[u][0] - cnt[u][0]);

    // 写入答案
    if (W) {
        auto pos = idx.find({ u, v });
        if (pos != idx.end()) {
            ans[(*pos).second] = { dp[u], dp[v] };
        }
        else {
            ans[(*idx.find({ v, u })).second] = { dp[v], dp[u] };
        }
    }

    trans(v, u);
}

void dfs1(int cur, int fa) {
    cnt[cur][(col[cur] == 'b' ? 0 : 1)] = 1;
    tot[cur][(col[cur] == 'b' ? 0 : 1)] = 1;

    for (auto &to : g[cur]) {
        if (to != fa) {
            dfs1(to, cur);
            trans(cur, to);
        }
    }
}

void dfs2(int cur, int fa) {
    for (auto &to : g[cur]) {
        if (to != fa) {
            inv(cur, to, true);
            dfs2(to, cur);
            inv(to, cur, false);
        }
    }
}

void solve()
{
    int n = 0;
    std::cin >> n >> col;
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        idx[{ u, v }] = i;
    }

    dfs1(0, 0);
    dfs2(0, 0);

    for (int i = 0; i < n - 1; i++) {
        std::cout << ans[i][0] << ' ' << ans[i][1] << '\n';
    }
    return;
}
```
</details>

## I

**题目大意**

在数轴上有若干不重复的特殊点，可以选择一个起点和长度 $d$，从一点开始，每次往前 $d$ 个单位。找到以个起点和长度 $d$，要求经过的特殊点最多。

**解题思路**

我们直接任意选择两个点，并且假设最优解经过这两个点。于是我们就可以枚举这两点间距离的质因数来作为步长，计算在经过选定的两个点的前提下，最多还可以经过多少个点。这样选点计算 100 百次，可以认为一定能得到最优解。

以下是证明：  
首先很容易想到过特殊点数量的一个下界：$max(奇数的个数，偶数的个数)$。而且这个下界一定是大于等于所有特殊点个数的一半的。若过有更优的解，则比这个下界还要大。我们就按最劣的情况来考虑，即最优解也只能经过一半的特殊点。此时我们在所有的特殊点中随机选择两个点，最优解经过经过这两个点的概率是 $\frac{1}{4}$，选择的两个点中至少有一个不被最优解经过的概率是 $\frac{3}{4}$。选择 100 组后至少选择到一组都被最优解经过的点的概率是 $1 - \frac{3}{4}^{100}$，是一个非常接近 1 的数，可以认为一定能至少选到一组。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

int main() {
    for (int i = 2; i * i < N; i++) {
        if (not vis[i]) {
            pri.push_back(i);
        }

        for (auto &p : pri) {
            int d = p * i;
            if (d * d >= N) {
                break;
            }
            vis[d] = true;
            if (i % p == 0) {
                break;
            }
        }
    }

    int n = 0;
    std::cin >> n;
    std::vector a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
    }

    if (n == 1) {
        std::cout << a[0] << ' ' << 2 << '\n';
        return 0;
    }

    std::array<int, 3> ans = { a[0], 2, 0 };
    for (int t = 0; t < T; t++) {
        int x = a[rnd() % n], y = 0;
        do {
            y = a[rnd() % n];
        } while (x == y);

        int d = std::abs(x - y);
        for (auto &p : pri) {
            if (p * p > d) {
                break;
            }
            if (d % p == 0) {
                while (d % p == 0) {
                    d /= p;
                }

                int cnt = 0;
                for (auto &i : a) {
                    if ((x - i) % p == 0) {
                        cnt++;
                    }
                }
                if (cnt > ans[2]) {
                    ans = { x % p, p, cnt };
                }

            }
        }

        if (d != 1) {
            int cnt = 0;
            for (auto &i : a) {
                if ((x - i) % d == 0) {
                    cnt++;
                }
            }
            if (cnt > ans[2]) {
                ans = { x % d, d, cnt };
            }
        }
    }

    std::cout << ans[0] << ' ' << ans[1] << '\n';
    return 0;
}
```
</details>

## J

模拟，建议直接看官方题解。

## K

**题目大意**

给定 $n$ 个序列，要求将这 $n$ 个序列合并，并且合并得到的序列的逆序数是 $k$。给出构造方案或判断不能。

合并的要求是：序列内的顺序不能变，但中间可以插入别的序列里的数。

保证：
- 这 $n$ 个序列的值域互不相交
- 序列的长度和 $\leq 10^3$

**解题思路**

首先序列内的顺序不变，所以我们就可以独立先计算出每个序列的逆序数，他们的和就是有解的 $k$ 的下界。构造这个下界就只用满足值域小的序列在前面就好了。同时我们也可以计算出有解的 $k$ 的上界，构造方法是值域大的序列在前面。由于每个序列的值域不相交，所以值域大的序列里的每一个数都大于值域小的序列里的任意一个数，根据这点我们可以很容易计算出上界。

于是对于界内的 $k$，我们都可以贪心地去构造。具体看代码注释。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    i64 mn = 0; // 下界
    std::vector v(n, std::vector<int>{});
    for (auto &a : v) {
        int l = 0;
        std::cin >> l;
        a.assign(l, 0);
        for (auto &i : a) {
            std::cin >> i;
        }

        // 计算 a 中的逆序对的数量
        for (int i = 0; i < l; i++) {
            for (int j = i + 1; j < l; j++) {
                if (a[i] > a[j]) {
                    mn++;
                }
            }
        }
    }
    
    // 值域大的序列在前面
    std::sort(v.begin(), v.end(), [&](const auto &x, const auto &y) {
        return x[0] > y[0];
    });
    i64 mx = mn; // 上界
    int len = 0;
    for (auto &a : v) {
        mx += len * a.size();
        len += a.size();
    }

    if (k < mn || k > mx) {
        std::cout << "No\n";
        return;
    }
    else {
        std::cout << "Yes\n";
    }

    // 只关注需要通过合并序列添加多少逆序对
    k -= mn;
    std::array<int, 2> idx = { -1, -1 };
    for (int i = 0; i < n && (idx[0] == -1); i++) { // 从值域最大序列的开始，尝试将其中的数放在前面
        len -= v[i].size(); // 放一个数导致的逆序数增量
        for (int j = 0; j < v[i].size(); j++) {
            if (len > k) { // 如果放在前面的增量多了，就记录下现在的位置，准备在后面找一个位置给它。
                idx = { i, j };
                break;
            }
            else { // 否则就直接放在前面
                k -= len;
                std::cout << v[i][j] << ' ';
            }
        }
    }
    // 为了不额外增加新的逆序对，还未开始合并的序列就直接正序输出
    for (int i = n - 1; (~idx[0]) && i > idx[0]; i--) {
        for (int j = 0; j < v[i].size(); j++) {
            std::cout << v[i][j] << ' ';
            len--; // 在此处插入前面记录的数对逆序数的增量
            if (len == k) { // 正好合适就插在此处，此逆序对剩下的数就放在最后面
                std::cout << v[idx[0]][idx[1]] << ' ';
            }
        }
    }
    // 最后的数
    for (int i = idx[1] + 1; (~idx[0]) && i < v[idx[0]].size(); i++) {
        std::cout << v[idx[0]][i] << ' ';
    }
    std::cout << '\n';
    
    return;
}
```
</details>

## L

找规律有点恶心，感觉还不如去打表。

以下是非打表代码。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector idx(n + 1, std::vector<int>{});
    for (int i = 0, m = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            // std::cout << m << '\t';
            idx[i].push_back(m++);
        }
        // std::cout << '\n';
    }
    
    std::cout << "Yes\n";
    for (int i = 0; i + 1 < n; i++) {
        std::cout << idx[i][0] << ' ';
    }
    for (int j = 0; j < n; j++) {
        std::cout << idx[n - 1][j] << ' ' << idx[n][j] << ' ' << idx[n][j + 1] << ' ' << idx[n - 1][j] << ' ';
    }
    for (int i = n - 2; i >= 0; i--) {
        std::cout << idx[i].back() << ' ';
        for (int j = i - 1; j >= 0; j--) {
            std::cout << idx[i + 1][j + 1] << ' ' << idx[i][j] << ' ';
        }
        for (int j = 1; j <= i; j++) {
            std::cout << idx[i][j] << ' ';
        }
    }
    std::cout << '\n';
    return;
}
```
</details>

## M

略
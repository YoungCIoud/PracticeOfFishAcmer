## A

犯唐了第一眼没看出来，写的时候又犯唐输入都没有就交了。

**解题思路**

判断有没有 1，有的话就输出 -1， 否则就输出一个大于数据范围的质数

**CODE**

```cpp
void solve()
{
    int n = 0;
    std::cin >> n;
    bool ok = true;
    for (int i = 1; i <= n; i++) {
        int x = 0;
        std::cin >> x;
        if (x == 1) {
            ok = false;
        }
    }
    std::cout << (ok ? Mod : -1) << '\n';
}
```

## B

**题目大意**

判断链

**解题思路**

直接记录每个点的度数，看度为1的节点是不是有两个，是的话有解，起点终点就是这两个点，否则没有。

**CODE**

```cpp
void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector d(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        d[u]++, d[v]++;
    }
    std::vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (d[i] == 1) {
            ans.push_back(i);
        }
    }
    if (ans.size() != 2) {
        std::cout << "-1\n";
    }
    else {
        std::cout << ans[0] << ' ' << ans[1] << '\n';
    }
}
```

## C

**题目大意**

给定一个边长为偶数 $n$ 的正方形 01 矩阵，保证其中 1 的数量正好占 $\frac{1}{4}$，你可以进行以下操作最多 $\frac{n^3}{2}$ 次：
- 交换矩阵中有公共边的两个格子（即相邻的两个格子）。

需要把所有的 1 通过以上操作全部调整到左上角的正方形中并输出操作的次数和每一步的操作。

**解题思路**

首先注意到题目中所说操作次数的上界，这个上界允许我们对每个 1 的移动次数最多可以达到 $2n$ （已经十分宽松了）。于是我们只要实现当一个 1 的位置确定之后， 后续的操作不会影响到这个 1 就好了。

具体的，假设我们正要找一个 1 给位置 $(u, v)$，我们先去列号大于等于 $v$ 的区域找（注意要忽略已经确定好的 1），如果在这个区域里找到了 1，那么移动的方式是先在列方向上移动再在行方向上移动；否则我们就要去行号大于 $u$ 的地方找，找到后移动的方式就是现在行方向上移动再在列方向上移动。

总之就是码力题。

**CODE**

```cpp
typedef std::array<int, 2> point;

std::vector<std::array<point, 2>> ans;
std::vector<std::string> g;

// 0: 对齐行
// 1: 对齐列
point align(point u, point v, int id) {
    int d = u[id] > v[id] ? -1 : 1;
    while (u[id] != v[id]) {
        auto uu = u;
        uu[id] += d;
        std::swap(g[u[0]][u[1]], g[uu[0]][uu[1]]);
        ans.push_back({ u, uu });
        u = uu;
    }
    return u;
}

// u -> v;
void move(point u, point v, int fir, int sec) {
    align(align(u, v, fir), v, sec);
    return;
}

void solve()
{
    ans.clear();

    int n = 0;
    std::cin >> n;
    g.assign(n, {});
    for (auto &s : g) {
        std::cin >> s;
    }
    
    for (int i = 0; i + i < n; i++) {
        for (int j = 0; j + j < n; j++) {
            if (g[i][j] == '1') {
                continue;
            }

            bool find = false;
            for (int y = j; y < n && not find; y++) {
                for (int x = (y + y < n ? i : 0); x < n && not find; x++) {
                    if (g[x][y] == '1') {
                        find = true;
                        move({ x, y }, { i, j }, 0, 1);
                    }
                }
            }

            for (int x = i + 1; x < n && not find; x++) {
                for (int y = j - 1; ~y && not find; y--) {
                    if (g[x][y] == '1') {
                        find = true;
                        move({ x, y }, { i, j }, 1, 0);
                    }
                }
            }
            // for (auto &s : g) {
            //     std::cout << s << '\n';
            // }
        }
    }

    std::cout << ans.size() << '\n';
    for (auto &[u, v] : ans) {
        std::cout << u[0] + 1 << ' ' << u[1] + 1 << ' ';
        std::cout << v[0] + 1 << ' ' << v[1] + 1 << '\n';
    }

    return;
}

```

## D

**题目大意**

定义双生数组是同时满足以下条件的数组：
1. 数组中只有两个不同的数
2. 这两个不同的数的数量相同

给出一个数组问是不是双生数组。

**解题思路**

根据定义即可。

**CODE**

```cpp
bool solve()
{
    int n = 0;
    std::cin >> n;
    std::map<int, int> m;
    for (int i = 1; i <= n; i++) {
        int x = 0;
        std::cin >> x;
        m[x]++;
    }
    if (m.size() != 2) {
        return false;
    }
    else {
        std::vector<int> a;
        for (auto &[ x, y ] : m) {
            a.push_back(y);
        }
        return a[0] == a[1];
    }
}
```

## E

**题目大意**

给出一个偶数长度的数组，可以进行以下操作任意次：
- 选择数组中的任意一个数进行加以或减一

问至少经过多少次操作可以使得该数组成为双生数组。

**解题思路**

首先要知道中位数定理：
- 所有数与中位数的绝对差之和最小

很容易看出这个绝对差之和就是把所有数调整成中位数所需要的操作次数。

在这题中，我们需要把所有的数分成两半，之后最优的做法就是分别将它们中的所有数调整成各自的中位数。

现在问题就来到了如何分才能使得最后的操作次数最少。显然通过排序来从中间分就好了。

**CODE**

```cpp
void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
    }
    std::sort(a.begin(), a.end());
    
    int m = n / 2;
    int mid1 = a[m - 1 >> 1] + a[m >> 1] >> 1;
    int mid2 = a[m + n - 1 >> 1] + a[m + n >> 1] >> 1;
    i64 ans = Inf;
    auto cnt = [&](int l, int r, int mid) -> i64 {
        i64 res = 0;
        for (int i = l; i < r; i++) {
            res += abs(mid - a[i]);
        }
        return res;
    };
    for (int i = -2; i <= 2; i++) {
        i64 res = cnt(0, m, mid1 + i);
        for (int j = -2; j <= 2; j++) {
            if (mid1 + i != mid2 + j) {
                ans = std::min(ans, res + cnt(m, n, mid2 + j));
            }
        }
    }
    std::cout << ans << '\n';
    return;
}
```

## F

**题目大意**

给出一个数组，问这个数组有多少个子数组是双生数组。

**解题思路**

假设我们已经找到了区间 $[l, r]$ ，这个区间由两个不同的数组成，而且这两个数的数量要尽可能多，于是在这个区间里面我们可以线性地统计出双生数组的数量。接下我们要找下一个这样的区间，而且我们可以知道下一个区间是由 $a[r]$ 和 $a[r + 1]$ 组成的。知道了这点后我们就可以以 $r$ 为中心线性地找左右边界，找到后统计。然后直到最边界。而且容易直到，每个数最多被包含在两个区间里，所以这个解法是线性的。

至于知道区间后如何统计数量，只用把区间里的一个数看成 1 ，另一个数看成 -1，然后找前缀相同的两个位置进行统计。

**CODE**

```cpp
void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    a.push_back(-1);

    // 需要保证 l 到 r 之间有且只有两个数。
    std::array<int, 2> num = { -1, -1 };
    auto cnt = [&](int l, int r) -> i64 {
        int len = r - l + 1, pre = len;
        std::vector tot(len * 2 + 1, 0);
        i64 res = 0;
        for (int i = 0; i < len; i++) {
            tot[pre]++;
            pre += (a[l + i] == num[0] ? 1 : -1);
            res += tot[pre];
        }
        return res;
    };

    int l = 0, r = 0;
    num[0] = a[l];
    while (a[r] == num[0]) {
        r++;
    }
    if (r != n) {
        num[1] = a[r];
        while (a[r + 1] == num[0] || a[r + 1] == num[1]) {
            r++;
        }
    }
    i64 ans = 0;
    if (~num[1]) {
        while (true) {
            ans += cnt(l, r);
            l = r++;
            if (a[r] == -1) {
                break;
            }
            num = { a[l], a[r] };

            while (a[l - 1] == num[0]) {
                l--;
            }
            while (a[r + 1] == num[0] || a[r + 1] == num[1]) {
                r++;
            }
        }
    }
    std::cout << ans << '\n';
    return;
}
```

## G

**题目大意**

给出一个数组，你可以进行如下操作若干次：
- 任选两个数，对其中一个加一，另一个减一。

问能否通过有限次操作将这个数组变成一个排列，能得话找到最小得操作次数。

**解题思路**

首先通过对数组求和来判断能否操作成排列，能得话就先对数组排序，然后从大到小依次操作成1， 2， 3，…… ， n。只用计算需要增加得地方就好了。

**CODE**

```cpp
void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n + 1, 0);
    i64 sum = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        sum += a[i] - i;
    }
    if (sum) {
        std::cout << "-1\n";
    }
    else {
        std::sort(a.begin() + 1, a.end());
        i64 ans = 0;
        for (int i = 1; i <= n; i++) {
            int d = a[i] - i;
            if (d > 0) {
                ans += d;
            }
        }
        std::cout << ans << '\n';
    }
}
```

## H

**题目大意**

在一个长度为 $n$ 的序列中，对于位置 $i$ 我可以放置 $[l_i, r_i]$ 中的数。问能不能将这个序列放置成为一个排列。

**解题思路**

我们先考虑有解的情况：  
我们按照从小到大的顺序依次找位置。对于数 1，它肯定是作为一段区间的左端点，我们贪心地把数 1 放在右端点最小的那个位置（因为右端点大的数它们放的数的范围更大，更有可能放其他的数）。在确定了 1 的位置后，那些 1 为左端点的区间都要看成是以 2 为左端点的区间，换句话说合并到左端点为 2 的那些区间里面去，再在这些区间中找右端点最小的。依此过程如果有解就可以确定所有的位置。

在此过程中，如果出现了区间的做端点大于右端点或者发现没有区间包含某个数，就可以判无解了。

上面的过程可以通过优先队列合并来实现。

**CODE**

```cpp
void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector idx(n + 1, 0);
    std::vector q(n + 1, std::priority_queue<std::pair<int, int>>{});
    for (int i = 1; i <= n; i++) {
        idx[i] = i;
        int l = 0, r = 0;
        std::cin >> l >> r;
        q[l].push({ -r, i });
    }

    // 将 q[v] 合并到 q[u] 上
    auto merge = [&](int u, int v) -> void {
        while (not q[v].empty()) {
            q[u].push(q[v].top());
            q[v].pop();
        }
        return;
    };

    bool ok = true;
    std::vector ans(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (q[idx[i]].empty()) {
            ok = false;
            break;
        }
        ans[q[idx[i]].top().second] = i;
        q[idx[i]].pop();

        if (not q[idx[i]].empty()) {
            if (i + q[idx[i]].top().first >= 0) {
                ok = false;
                break;
            }
            else if (q[idx[i]].size() > q[i + 1].size()) {
                merge(idx[i], i + 1);
                idx[i + 1] = idx[i];
            }
            else {
                merge(i + 1, idx[i]);
            }
        }
    }
    if (ok) {
        for (int i = 1; i <= n; i++) {
            std::cout << ans[i] << " \n"[i == n];
        }
    }
    else {
        std::cout << "-1\n";
    }
    return;
}
```

## J

**题目大意**

问数组中有多少对数满足两数得gcd等于两数按位异或的结果。

**解题思路**

令 $gcd(x, y) = g$，则我们要找满足 $x \oplus y = g$ 的 $x$ 和 $y$。 根据异或的性质，我们在式子的两边同时异或 $x$ 就得到了 $y = g \oplus x$， 显然 $g$ 一定是 $x$ 的因数，而且因数个数最多有 $2^7$ 个（因为前 7 个质数的乘积已经超出数据范围了）。 于是从大到小枚举 $x$，对于每个 $x$ 枚举它的因数，以此因数来找 $y$ 检查 gcd 满不满足。满足的话对答案的贡献就是两个数的个数的乘积。

最后注意对答案除 2。

**CODE**

```cpp
std::vector<int> p;
bool vis[1001];
std::vector<std::array<int, 2>> fac;

void dfs(int idx, int f, std::vector<int> &res) {
    res.push_back(f);
    for (int i = idx; i < fac.size(); i++) {
        for (int j = 0, k = fac[i][0]; j < fac[i][1]; j++, k *= fac[i][0]) {
            dfs(i + 1, f * k, res);
        }
    }
}

std::vector<int> find(int x) {
    fac.clear();
    for (auto &f : p) {
        if (f * f > x) {
            break;
        }
        if (x % f == 0) {
            fac.push_back({ f, 0 });
        }
        while (x % f == 0) {
            fac.back()[1]++;
            x /= f;
        }
    }
    if (x != 1) {
        fac.push_back({ x, 1 });
    }

    std::vector<int> res;
    dfs(0, 1, res);
    return res;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector cnt(N + 1, 0);
    for (int i = 0; i < n; i++) {
        int x = 0;
        std::cin >> x;
        cnt[x]++;
    }
    
    i64 ans = 0;
    for (int i = 1; i <= N; i++) {
        if (cnt[i] == 0) {
            continue;
        }
        // std::cout << i << ":\t";
        for (auto f : find(i)) {
            // std::cout << f << ' ';
            int j = i ^ f;
            if (std::__gcd(i, j) == f && j <= N) {
                ans += 1ll * cnt[i] * cnt[j];
            }
        }
        // std::cout << '\n';
    }
    std::cout << ans / 2ll << '\n';
}
```

## K

**题目大意**

问数组中有多少个区间满足区间 gcd 等于区间异或和。

**解题思路**

首先基础的，可以用 st 表快速求区间 gcd，用异或前缀和快速求区间异或和。

其次，对于一个区间，将它的范围慢慢放大，则这个区间的区间 gcd 在放大的过程中至多有 $log_2A$ 个不同的数（$A$ 是区间中最大的数）。于是对于一个固定的区间左端点 $l$，我们可以找到全部的右端点 $r_i$（令 $r_0 = l$）使得 $gcd([l, r_i]) \not = gcd([l, r_i - 1])$，而且对于每个固定左端点它的右端点的数量是 $log$ 级别的。于是我们的任务就是在异或前缀和数组的 $[r_{i - 1}, r_i - 1]$ 里统计 $gcd([l, r_{i - 1}]) \oplus (\oplus_{i = 0}^{l - 1}a_i)$ （用 $tar$ 表示这个数）的数量。

对于统计区间内某个数的数量，我们可以维护出每个数出现在了数组的那些位置，然后对左右端点在维护出来的位置数组上二分就好了。

注意最后的答案需要减去原数组的长度，因为答案不能包括长度为 1 的区间。

**CODE**

```cpp
void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector st(n + 1, std::vector(L, 0));
    std::vector pre(n + 1, 0);
    std::map<int, std::vector<int>> pos;
    for (int i = 1; i <= n; i++) {
        std::cin >> st[i][0];
        pre[i] = pre[i - 1] ^ st[i][0];
        pos[pre[i]].push_back(i);
    }
    for (int l = 1; l < L; l++) {
        for (int i = 1; i + (1 << l) - 1 <= n; i++) {
            st[i][l] = std::__gcd(st[i][l - 1], st[i + (1 << l - 1)][l - 1]);
        }
    }
    auto quiry = [&](int l, int r) -> int {
        int len = log2(r - l + 1);
        return std::__gcd(st[l][len], st[r - (1 << len) + 1][len]);
    };

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int mn_g = quiry(i, n);
        int l = i, g = st[l][0], tar = g ^ pre[i - 1];
        while (g != mn_g) {
            int r = 0;
            for (int j = L; j >= 0; j--) {
                int rr = r | (1 << j);
                if (rr <= l || (rr <= n && quiry(i, rr) == g)) {
                    r = rr;
                }
            }

            ans += std::upper_bound(pos[tar].begin(), pos[tar].end(), r) - std::lower_bound(pos[tar].begin(), pos[tar].end(), l);
            l = r + 1;
            g = quiry(i, l);
            tar = g ^ pre[i - 1];
        }

        ans += pos[tar].end() - std::lower_bound(pos[tar].begin(), pos[tar].end(), l);
    }

    std::cout << ans - n << '\n';
}
```

## L

**题目大意**

给出一个长度为 $n$ 的 01 串，你可以进行一下操作至多 $n^2$次：
- 选择连续的 $x$ 个位置，将这些位置上的数取反
- 选择连续的 $y$ 个位置，将这些位置上的数取反

问是否能够将串操作成全 1。能得话还要输出依次对那些串操作。

$1 \leq x, y \leq \frac{n}{3}$

**解题思路**

假设 $x < y$，则我们可以先保证前 $n - x + 1$ 个数全是 1（每次反转长度为 $x$ 的就好了），对于后面的 $x - 1$ 个数，除非我们能只对一个长度小于 $x$ 的区间进行反转，否则我们再没有任何办法了。这就是 $y$ 的意义 —— 和 $x$ 进行组合使得能对更小的区间反转。很容易想出这个最小的长度就是两数的gcd（若干个数的线性组合的结果是他们 gcd 的倍数）。具体的对于需要反转的区间 $[l, r)$，$+x$ 就是对 $[l - x, l)$ 反转使得需要反转的区间变成 $[l - x, r]$；$-y$ 就是对 $[l, l + y)$ 反转使得需要反转的区间变成 $[l + y, r]$；为了不超出原串的左边界，当能 $-y$ 我们就要进行 $-y$ 操作（缩减区间），这样就最终一定使 $l = r$，即在效果上对长度为 $gcd(x, y)$ 的区间进行了反转。这已经是可以单独反转的最小区间，如果对于后面的 $x - 1$ 个数用这个区间反转仍不能满足要求，那就真不能了。

**CODE**

```cpp
void solve()
{
    int n = 0, x = 0, y = 0;
    std::string s;
    std::cin >> n >> x >> y >> s;
    if (x > y) {
        std::swap(x, y);
    }

    // [l, r)
    std::vector<std::array<int, 2>> ans;
    for (int i = 0; i + x <= n; i++) {
        if (s[i] == '1') {
            continue;
        }

        ans.push_back({ i, i + x });
        for (int j = i; j < i + x; j++) {
            s[j] ^= 1;
        }
    }

    int g = std::__gcd(x, y);
    for (int i = 0; i + g <= n; i++) {
        if (s[i] == '1') {
            continue;
        }
        int l = i, r = l + g;
        for (int j = l; j < r; j++) {
            s[j] ^= 1;
        }
        while (l < r) {
            if (r - l < y) {
                ans.push_back({ l - x, l });
                l -= x;
            }
            else {
                ans.push_back({ l, l + y });
                l += y;
            }
        }
    }

    if (s == std::string(n, '1')) {
        assert(ans.size() <= n * n);
        std::cout << ans.size() << '\n';
        for (auto &[l, r] : ans) {
            std::cout << l + 1 << ' ' << r << '\n';
        }
    }
    else {
        std::cout << "-1\n";
    }

    return;
}
```

## M

**题目大意**

在一个数组里面，选定一个非空的区间，并将区间里的所有数都乘 2。问极差最大是多少。

**解题思路**

给定的操作是一个放大的操作，我们肯定想要将最小值放大。若我们想要放大最小值，我们选的区间必须包含所有的最小值，因为如果还有最小值在区间外，那么我们放大后最小值还是不变，这样的操作是无意义的。

于是我们可以的区间可以由小到达慢慢拓展：从只包含一个最小值，到包含所有的最小值，再到包含已选区间外所有的最小值……。对于区间每个大小时的答案取最小就好了。

拓展操作可以通过最值前后缀来 $O(n)$ 地完成，也可以排序着做。


**CODE**

```cpp
int n;
int a[N + 5];
int mxp[N + 5], mnp[N + 5]; // 前后缀最小值
int mxs[N + 5], mns[N + 5]; // 前后缀最大值

void solve()
{
    std::cin >> n;
    mnp[0] = mns[n + 1] = Inf;

    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        mxp[i] = std::max(mxp[i - 1], a[i]);
        mnp[i] = std::min(mnp[i - 1], a[i]);
    }
    for (int i = n; i >= 1; i--) {
        mxs[i] = std::max(mxs[i + 1], a[i]);
        mns[i] = std::min(mns[i + 1], a[i]);
    }
    a[0] = a[n + 1] = Inf;

    int ans = Inf;
    if (n == 1 || mxs[1] == mns[1]) {
        ans = 0;
    }
    else {
        int l = 1;
        while (mns[l] != a[l]) l++;
        int r = l;
        ans = std::max(mxs[1], a[l] * 2) - std::min({ mnp[l - 1], mns[r + 1], 2 * a[l] });

        int mx = 0, tar = std::min(mnp[l - 1], mns[r + 1]);
        while (r <= n || l >= 1) {
            while (l >= 1 && mnp[l - 1] == tar) {
                mx = std::max(mx, a[l]);
                l--;
            }
            while (r <= n && mns[r + 1] == tar) {
                mx = std::max(mx, a[r]);
                r++;
            }
            mx = std::max({ mx, a[l], a[r] });
            l = std::max(l, 1) - 1;
            r = std::min(r, n) + 1;
            ans = std::min(ans, std::max({ mx * 2, mxp[l], mxs[r]}) - std::min({ mns[1] * 2, mnp[l], mns[r] }));
        }
    }
    std::cout << ans << '\n';
}
```
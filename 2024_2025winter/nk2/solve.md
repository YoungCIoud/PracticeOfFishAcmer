## A

略

## B

略

## C

（欲看此题，请先看 D 题题解）

**题目大意**

给定串长和串值，构造串。

**解题思路**

跟 D 对拍慢慢调……（~~其实是讲不出思路~~）。

**CODE**

<details>
<summary>点击查看代码</summary>

```
void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    int d = n - m;
    std::string ans;
    if (d == 0 || d > 26) {
        ans = "NO";
    }
    else if (m == 1) {
        if (n > 27) {
            ans = "NO";
        }
        else {
            std::string s;
            for (int i = 0, c = 'a'; i < n - 1; i++, c++) {
                s.push_back(char(c));
            }
            ans = "YES\n" + s + "a";
        }
    }
    else if (d + d >= n) {
        if (n > 56) {
            ans = "NO";
        }
        else {
            std::string s(n, '?');
            int l = d, r = n - 1 - d;
            s[0] = s[l] = 'a';
            s[n - 1] = s[r] = 'b';
            for (int i = 1, c = 'c'; i < l; i++) {
                if (s[i] == '?')
                {
                    s[i] = char(c++);
                }
            }
            for (int i = n - 2, c = 'c'; i > l; i--) {
                s[i] = char(c++);
            }
            ans = "YES\n" + s;
        }
    }
    else {
        std::string s(n - 2 * d, 'a');
        std::string ss{};
        for (int i = 0; i < d; i++) {
            ss.push_back('a' + i);
        }
        s = ss + s;
        std::reverse(ss.begin(), ss.end());
        ans = "YES\n" + (s + ss);
    }
    std::cout << ans << '\n';
    return;
}
```
</details>

## D

**题目大意**

定义一个字符串的值是最大的 $K$，使得存在一个长度为 $K$ 的子串与一个长度为 $K$ 的子序列相等，要求这个子序列至少由两个子串构成。给定一个串问串值

**解题思路**

我们只用关注第一次出现重复字母的位置，比如 `ab**b***` 我们在第 5 个位置找到重复的字母 `b`，于是可能的答案就是 $8 - 5 + 1$，同样的操作对反串算一次又得到一个可能的答案，两者取小就好了。

**CODE**

<details>
<summary>点击查看代码</summary>

```
int solve(int n, std::string s)
{
    s = "#" + s;

    std::vector cnt(26, 0);
    int ans = 0;
    for (int i = n; i >= 1; i--) {
        int m = cnt[s[i] - 'a']++;
        if (m) {
            ans = i;
            break;
        }
    }
    return ans;
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        int n = 0;
        std::string s;
        std::cin >> n >> s;
        auto ss = s;
        std::reverse(s.begin(), s.end());
        std::cout << std::max(solve(n, ss), solve(n, s)) << '\n';
    }

    sp();

    return 0;
}
```
</details>

## E

**题目大意**

有一排多米诺骨牌，每个位置的骨牌都有一个重量，一开始可以推倒任意重量的一个骨牌，当前倒下的骨牌能推到下一个骨牌当且仅当已经倒下的骨牌的重量之和大于等于下一个骨牌。

你可以进行如下操作：
- 任选一个骨牌，将其重量加一或者是减一。

相互独立地给出多个 $l,r$，问对于每对 $l,r$，想要推到第 $l$ 个骨牌后第 $r$ 个骨牌也能倒下，一开始至少要进行多少次操作。

**解题思路**

首先注意到：在区间中，对于除了第一个的其他骨牌，对其重量减一就相当于对区间第一张牌的重量加一。

其次，在区间中，如果我们通过增重第一张牌使后面“最难倒下”的牌倒下了，那其他的都可以倒下。衡量“难倒下”就是看某张牌与他前面倒下的牌总重量之差。差为非正数说明不用操作就可以倒下，否则就要对第一张牌增重。“最难倒下”的就是这个差最大的。

在之后就是区间找最值了，假设第一张牌倒下去维护区间里上述差值的最大值。在询问时就直接找区间的最大差值，再加上左端点前面一个数的前缀。

**CODE**

<details>
<summary>点击查看代码</summary>

```
void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::vector a(n + 1, 0ll), pre(n + 1, 0ll);
    std::vector st(n + 1, std::vector(L, 0ll));
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        st[i][0] = a[i] - pre[i - 1];
        pre[i] = pre[i - 1] + a[i];
    }
    
    for (int l = 1; l < L; l++) {
        for (int i = 1; i + (1 << l) - 1 <= n; i++) {
            st[i][l] = std::max(st[i + (1 << l - 1)][l - 1], st[i][l - 1]);
        }
    }
    auto quiry = [&](int l, int r) -> i64 {
        int len = log2(r - l + 1);
        return std::max(st[l][len], st[r - (1 << len) + 1][len]);
    };

    while (q--) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        i64 ans = 0;
        if (l != r) {
            i64 mx = quiry(l + 1, r);
            mx += pre[l - 1];
            ans = std::max(ans, mx);
        }
        std::cout << ans << '\n';
    }
    return;
}
```
</details>

## F

**题目大意**

在一个整数区间内找出满足 $x + y = x \& y + x | y + x \oplus y$ 的 $<x, y>$ 数对的数量

**解题思路**

考虑单独一位上：
- $0 + 0 = 0 + 0 + 0$
- $0 + 1 < 0 + 1 + 1$
- $1 + 0 < 0 + 1 + 1$
- $1 + 1 = 1 + 1 + 0$

可以看到，对于任意的 $x, y$，$x + y \leq x \& y + x | y + x \oplus y$，当且仅当 $x = y$ 时取等号。


## G

注意开 longlong 就好了。略。

## H

**题目大意**

在给定矩形的边框上找三个互不相同且不共线的点，使得这三个点所确定的圆的半径最大。

**解题思路**

一句话：圆心是中垂线的交点

根据这句话画画图看圆心的是怎么随点动的就好了。

**CODE**

<details>
<summary>点击查看代码</summary>

```
void solve()
{
    int a = 0, b = 0, c = 0, d = 0;
    std::cin >> a >> b >> c >> d;
    std::cout << b << ' ' << d << '\n';
    int w = b - a, h = d - c;
    if (w >= h) {
        std::cout << b - 1 << ' ' << d << '\n';
        std::cout << a << ' ' << d - 1 << '\n';
    }
    else {
        std::cout << b << ' ' << d - 1 << '\n';
        std::cout << b - 1 << ' ' << c << '\n';
    }
    return;
}
```
</details>


## I

**题目大意**

给定一颗树，计算所有连通块中点对异或和的和的和，即 $\sum_V\sum_{i,j \in V}a_i \oplus a_j$

**解题思路**

首先 $\sum_{i,j}a_i \oplus a_j = 2 \times \sum_{i < j}a_i \oplus a_j$， 也就是说如果我们先计算右边的式子，那么最后乘 2 才是答案（左边的式子就是要我们在计算的过程中乘 2）。下面看如何计算右边的式子。

此题最重要的观察就是每一位都是相互独立的可以单独计算。

假设我们已经计算出来两个子树的答案 $f[u]$ 和 $f[v]$，现在我们要将 $f[v]$ 合并到 $f[u]$ 里面。我们考虑两种点对的贡献：第一种是点对中的两点都只在同一个子树中；剩下的就是第二种。  
计算第一种的贡献就是计算 $f[u]$ 和 $f[v]$ 的贡献。对于 $f[u]$ 的贡献我们要计算出两个子树合并后新增了多少个包含子树 $u$ 的连通块，为此我们要维护出子树 $v$ 中包含节点 $v$ 的连通块的数量：$num[v]$，于是 $f[u]$ 的贡献就是 $f[u] \times num[v]$，$f[v]$ 的贡献同理计算。其中 $num[u]$ 的转移就是 $$num[u] = num[u] + num[u] \times num[v]$$  
对于第二种，我们就需要一位位地算了。考虑第 $i$ 位（最低位是第 0 位），计算该位产生的贡献主要是计算第二种点对中有多少在该位上的异或和是 1。自然的想到对于每一位我们还需要维护出子树中 0 和 1 的数量 $cnt[u][i][0]$ 和 $cnt[u][i][1]$，然后贡献就是
$$(cnt[u][i][1] \times cnt[v][i][0] + cnt[u][i][0] \times cnt[v][i][1]) << i$$
由于点对需要在同一个连通块中，所以对于子树 $u$ 我们要维护的 $cnt[u][i]$ 的具体作用是：统计子树 $u$ 里**所有包含 $u$ 的连通块**中的节点第 $i$ 位 0 和 1 的数量，转移就是
$$cnt[u][i][bit] = cnt[u][i][bit] + cnt[u][i][bit] \times num[v] + cnt[v][i][bit] \times num[u]$$

所以总的，在合并的过程中我们有如下转移：
$$f[u] = f[u] + f[u] * num[v] + f[v] * num[u]$$
$$f[u] = f[u] + ((cnt[u][i][1] \times cnt[v][i][0] + cnt[u][i][0] \times cnt[v][i][1]) << i)$$
$$cnt[u][i][bit] = cnt[u][i][bit] + cnt[u][i][bit] \times num[v] + cnt[v][i][bit] \times num[u]$$
$$num[u] = num[u] + num[u] \times num[v]$$

有了如上转移，就可以树上 dp 了。最后的答案就是
$2 
\times \sum f[i]$。

**CODE**

<details>
<summary>点击查看代码</summary>

```
constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, M = 1e9, Inf = 1e9, L = 30;
std::vector<int> a(N + 5), g[N + 5];
i64 f[N + 5], cnt[N + 5][L][2], num[N + 5];

void dfs(int cur, int fa) {
    f[cur] = 0, num[cur] = 1;
    for (int i = 0; i < L; i++) {
        cnt[cur][i][a[cur] >> i & 1] = 1;
    }
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }
        dfs(to, cur);
        (f[cur] += f[to] * num[cur] + f[cur] * num[to]) %= Mod;
        for (int i = 0; i < L; i++) {
            (f[cur] += ((cnt[cur][i][0] * cnt[to][i][1] + cnt[cur][i][1] * cnt[to][i][0]) % Mod << i)) %= Mod;
            (cnt[cur][i][0] += cnt[cur][i][0] * num[to] + cnt[to][i][0] * num[cur]) %= Mod;
            (cnt[cur][i][1] += cnt[cur][i][1] * num[to] + cnt[to][i][1] * num[cur]) %= Mod;
        }
        (num[cur] += num[cur] * num[to]) %= Mod;
        debug("%d:\t%d\n", to, f[cur]);
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);
    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        (ans += f[i]) %= Mod;
    }
    std::cout << (ans << 1) % Mod << '\n';
    return;
}
```
</details>

## J

按题模拟即可

**CODE**

<details>
<summary>点击查看代码</summary>

```
class Time {
public:
    int h, m, s;
    Time(int hh, int mm = 0, int ss = 0): h(hh), m(mm), s(ss) {}
    bool operator<=(Time &a) {
        if (h == a.h) {
            if (m == a.m) {
                return s <= a.s;
            }
            else {
                return m < a.m;
            }
        }
        else {
            return h < a.h;
        }
    }
};

Time work1l(7),  work1r(9);
Time work2l(18),  work2r(20);
Time napl(11), napr(13);
Time slp1l(22), slp1r(23, 59, 59);
Time slp2l(0), slp2r(1);

bool chk(Time &u, Time &x, Time &v) {
    return u <= x && x <= v;
}

void solve()
{
    int n = 0, h = 0, m = 0;
    std::cin >> n >> h >> m;
    std::map<std::string, bool> vwork, vslp, vnap;
    int work = 0, slp = 0, nap = 0;
    for (int i = 0; i < n; i++) {
        std::string id;
        int Y = 0, Mo = 0, D = 0;
        int H = 0, Mi = 0, S = 0;
        std::cin >> id;
        scanf("%d-%2d-%2d %2d:%2d:%2d", &Y, &Mo, &D, &H, &Mi, &S);
        if (Y == h && Mo == m) {
            Time t(H, Mi, S);
            if ((chk(work1l, t, work1r) || chk(work2l, t, work2r)) && not vwork[id]) {
                vwork[id] = true;
                work++;
            }
            else if (chk(napl, t, napr) && not vnap[id]) {
                vnap[id] = true;
                nap++;
            }
            else if ((chk(slp1l, t, slp1r) || chk(slp2l, t, slp2r)) && not vslp[id]) {
                vslp[id] = true;
                slp++;
            }
        }
    }
    std::cout << work << ' ' << nap << ' ' << slp << '\n';
    return;
}
```
</details>


## K

**题目大意**

一张玻璃网格上有两种玻璃，一种是易碎玻璃，一种是普通玻璃。一个普通玻璃可以离开网格当且仅当与这块玻璃相邻的普通玻璃可以掉落并且不和易碎玻璃共边。问为了至少让一块玻璃离开网格，至少要敲掉多少易碎玻璃。

**解题思路**

直接对每块连通的普通玻璃 dfs 算答案取最小值就好了。

**CODE**

<details>
<summary>点击查看代码</summary>

```
constexpr int N = 500, M = 500, Inf = 1e9;
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int vis[500][500], cnt;

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector g(n, std::string{});
    for (auto &s : g) {
        std::cin >> s;
    }
    auto dfs = [&](auto self, int x, int y, int &res) -> void {
        vis[x][y] = cnt;
        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (xx < 0 || xx >= n || yy < 0 || yy >= m || vis[xx][yy] == cnt) {
                continue;
            }
            if (g[xx][yy] == '0') {
                res++;
                vis[xx][yy] = cnt;
            }
            else {
                self(self, xx, yy, res);
            }
        }
    };

    int ans = Inf;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '0' || vis[i][j] != 0) {
                continue;
            }
            int res = 0;
            cnt++;
            dfs(dfs, i, j, res);
            ans = std::min(ans, res);
        }
    }
    std::cout << ans << '\n';
}
```
</details>

## M

**题目大意**

在一个 $3 \times n$ 的矩阵中，每个 $3 \times 3$ 的子矩阵都要求同时满足以下两点：
- 子矩阵中的数字 $\in [1, 9]$
- 子矩阵中的数字重复

在给出的矩阵中，有一些是 `?` 表示待填的数字，问有多少种合法的填数方案。

**解题思路**

最重要的一点观察就是：对模 3 同余的列号上的数字种类是一样的。

观察出这点后就是常规的组合排列了。

**CODE**

<details>
<summary>点击查看代码</summary>

```
void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector g(3, std::string{});
    std::vector cnt(4, std::vector(10, 0ll));
    for (auto &s : g) {
        std::cin >> s;
        for (int i = 0; i < n; i++) {
            if (s[i] != '?') {
                int d = (cnt[i % 3][s[i] - '0'] == 0) ? 1 : 0;
                cnt[i % 3][0] += d;
                cnt[3][s[i] - '0'] += d;
                cnt[i % 3][s[i] - '0'] = 1;
            }
        }
    }
    
    // 有解判断
    bool ok = true;
    if (cnt[0][0] > 3 || cnt[1][0] > 3 || cnt[2][0] > 3) {
        ok = false;
    }
    for (int i = 1; i <= 9 && ok; i++) {
        if (cnt[3][i] > 1) {
            ok = false;
        }
    }
    std::vector nuknow(n, 0);
    for (int j = 0; j < n && ok; j++) {
        for (int i = 0; i < 3 && ok; i++) {
            if (g[i][j] == '?') {
                nuknow[j]++;
                continue;
            }
            for (int k = i + 1; k < 3 && ok; k++) {
                if (g[i][j] == g[k][j]) {
                    ok = false;
                }
            }
        }
    }

    std::vector fac(10, 1);
    for (int i = 1; i <= 9; i++) {
        fac[i] = fac[i - 1] * i;
    }
    i64 ans = 0;
    if (ok) {
        ans = 1ll * fac[9 - (cnt[0][0] + cnt[1][0] + cnt[2][0])] / (fac[3 - cnt[0][0]] * fac[3 - cnt[1][0]] * fac[3 - cnt[2][0]]);
        for (int j = 0; j < n; j++) {
            (ans *= 1ll * fac[nuknow[j]]) %= Mod;
        }
    }

    std::cout << ans << '\n';
}
```
</details>

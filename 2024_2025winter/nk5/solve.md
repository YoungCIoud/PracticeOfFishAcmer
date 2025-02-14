## A

略

## B

贴个代码就完了

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
void solve()
{
    int n = 0, t = 0, k = 0;
    std::cin >> n >> t >> k;
    int ans = (n - k) / t;
    if (ans - 1 >= k) {
        ans = k + 1;
    }
    std::cout << ans << '\n';
}
```
</details>

## C

**题目大意**

以 01 串的形式给出 3 个数 $A$、$B$、$C$。可以对 $A$ 或 $B$ 进行的操作有：
- 以 $x$ 的代价反转一位
- 在一个数中选两位以 $y$ 的代价交换这两位

问至少需要花费多少代价才能使得 $A \oplus B = C$

**解题思路**

首先容易想到当 $2x \leq y$ 时，全部选第一个操作就好了。否则应该优先选择操作 2，而且每次使用操作 2 时应该能同时使两位合法。

可以把所有不合法的位分为 4 类：
- 0：在该位上 $A$ 为 0，$B$ 为 0；
- 1：在该位上 $A$ 为 0，$B$ 为 1；
- 2：在该位上 $A$ 为 1，$B$ 为 0；
- 3：在该位上 $A$ 为 1，$B$ 为 1；

由于对于每个不和法的位，我们只需要在两个数中任选一个来反转该位就能使该位合法，所以上述 4 类不合法的位（包含了所有不合法的位），能够选择其他 3 类来进行操作 2。比如第 0 类和第 1 类就在 $B$ 上做交换，第 0 类和第 2 类就在 $A$ 上做交换。

所以问题又变成了有 4 种颜色的小球，不同颜色的小球间可以两两配对，求最多能配多少对。  
这种问题不管有几种颜色，解法都是统一的，即先看数量最多的球是否超过到总数的一半，超过就其他的球都和它配对，最后还有剩的就不能再配对了。否则配对数直接就是总数除 2 向下取整，如果总数是奇数最后就会剩下一个球。

知道了能进行多少次交换操作后，剩下的就都是操作 1 了。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
void solve()
{
    i64 n = 0, x = 0, y = 0;
    std::cin >> n >> x >> y;
    std::string a, b, c;
    std::cin >> a >> b >> c;
    std::vector cnt(4, 0ll);
    for (int i = 0; i < n; i++) {
        if (c[i] == '0') {
            if (a[i] == '0' && b[i] == '1') {
                cnt[1]++;
            }
            else if (a[i] == '1' && b[i] == '0') {
                cnt[2]++;
            }
        }
        else {
            if (a[i] == '0' && b[i] == '0') {
                cnt[0]++;
            }
            else if (a[i] == '1' && b[i] == '1') {
                cnt[3]++;
            }
        }
    }

    i64 sum = cnt[0] + cnt[1] + cnt[2] + cnt[3];
    if (x * 2 <= y) {
        std::cout << x * sum << '\n';
    }
    else {
        std::sort(cnt.begin(), cnt.end());
        if (cnt[3] * 2 >= sum) {
            i64 num = sum - cnt[3];
            std::cout << y * num + x * (cnt[3] - num) << '\n';
        }
        else {
            std::cout << y * (sum / 2) + x * (sum % 2) << '\n';
        }
    }

    return;
}
```
</details>

## D

**题目大意**

在 01 数组 $A$ 中，从第一个数开始，每 $k$ 个数划分一段，如果最后一段不足 $k$ 个数的也算作一段，在划分出来的每一段内，可以进行如下操作任意顺序任意次：
- 将段内所有的数 01 互换。
- 任意排列段内的数。

将操作后得到的序列中所有连续相同的数都变成一个数后得到一个 01 相间的序列，我们定义 $f(k)$ 为最后的到的这个序列长度的最小值。

求 $\oplus_{i = 1}^{n}f(i)$。

**解题思路**

根据题目描述的操作，我们要知道如果某一段中有若干数量大于 0 的 0 和 1，我们就可以把这段看成 `10`，如果某一段中只有一个数，不管是 0 还是 1 我们都可以把这段看成 `00`。于是接下来我们考虑，$x$ 段 `10` 拼成的序列通过合并连续相同的数最短能达到多长。答案是 $x + 1$（比如有 3 段，就这样拼 `100110`）。再考虑如果 $x$ 段中有 $y$ 段 `10` 变成了 `00`，能达到的最短长度是多少。答案是 $x + 1 - y$。

于是我们就可以这么来处理：先令 $f(i) = \lceil \frac{n}{i} \rceil + 1$，即假设分成的所有段都可以看成 `10`。然后再去计算每段长度为 $i$ 时有多少段全是相同的数，初始的值减去这个数量就是我们要的精确的值了。注意一下最后一段的处理就好了。时间复杂度是线性的。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n;
    std::cin >> s;
    std::vector ans(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        ans[i] += (n + i - 1) / i; // n / i 向上取整
    }

    for (int l = 0, r = 0; l < n; l = r) {
        while (r < n && s[l] == s[r]) {
            r++;
        }
        int len = r - l;
        for (int k = 1; k <= len; k++) {
            int ll = (l + k - 1) / k * k;
            ans[k] -= (r - ll) / k;
            if (r == n && (r - ll) % k != 0) {
                ans[k]--;
            }
        }
        if (r == n) {
            for (int k = len + 1; k <= n; k++) {
                if ((l + k - 1) / k * k < r) {
                    ans[k]--;
                }
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        res ^= ans[i];
    }
    std::cout << res << '\n';
}
```
</details>

## E

**题目大意**

给定一个未分出胜负的三子棋局面，且双方走了相同的步数。问让白子先走两步白子能否必胜。

**解题思路**

当各走走了 2 步以下时，白子是必胜的。

当各走了 4 步时，由于只剩下一个位置，所以下完检查以下就好了。

当各走了 3 步，还剩下 3 个位置，$C_3^2$ 枚举所有情况即可。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
bool chk() {
    for (int i = 0; i < 3; i++) {
        if (g[i] == "XXX") {
            return true;
        }
    }

    for (int j = 0; j < 3; j++) {
        bool line = true;
        for (int i = 0; i < 3; i++) {
            if (g[i][j] != 'X') {
                line = false;
                break;
            }
        }
        if (line) {
            return true;
        }
    }

    if (g[1][1] == 'X' && g[0][0] == 'X' && g[2][2] == 'X') {
        return true;
    }
    if (g[1][1] == 'X' && g[0][2] == 'X' && g[2][0] == 'X') {
        return true;
    }

    return false;
}

void chg(std::array<int, 2> p, char c) {
    g[p[0]][p[1]] = c;
}

bool solve()
{
    int cnt = 0;
    std::vector<std::array<int, 2>> pos;
    for (int i = 0; i < 3; i++) {
        std::cin >> g[i];
        for (int j = 0; j < 3; j++) {
            if (g[i][j] == 'X') {
                cnt++;
            }
            else if (g[i][j] == 'G') {
                pos.push_back({ i, j });
            }
        }
    }

    if (cnt <= 2) {
        return true;
    }
    else if (cnt == 4) {
        chg(pos[0], 'X');
        return chk();
    }
    else {
        for (int i = 0; i < 3; i++) {
            chg(pos[i], 'X'), chg(pos[(i + 1) % 3], 'X');
            if (chk()) {
                return true;
            }
            chg(pos[i], 'G'), chg(pos[(i + 1) % 3], 'G');
        }
    }

    return false;
}

```
</details>

## H

**题目大意**

将一个长度为 $n$ 的数组划分成 $k$ 段，求在所有的划分方案中，所有区间的区间最大值乘区间最小值之和。

**解题思路**

这种题一般是要单独算贡献。所以直接枚举所有区间，再看有多少划分方案是包含这个区间的就好了。用隔板法考虑，注意下当枚举到的区间是最左边或者最右边的情况。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Mod;
        }
    }

    std::vector st(n, std::vector(L, std::array<i64, 2>{ 0, 0 }));
    for (int i = 0; i < n; i++) {
        std::cin >> st[i][0][0];
        st[i][0][1] = st[i][0][0];
    }

    for (int l = 1; l < L; l++) {
        for (int i = 0; i + (1 << l) <= n; i++) {
            st[i][l][0] = std::max(st[i][l - 1][0], st[i + (1 << l - 1)][l - 1][0]);
            st[i][l][1] = std::min(st[i][l - 1][1], st[i + (1 << l - 1)][l - 1][1]);
        }
    }
    // 左闭右开
    auto quiry = [&](int l, int r) -> i64 {
        int len = log2(r - l);
        int m = r - (1 << len);
        return std::max(st[l][len][0], st[m][len][0]) * std::min(st[l][len][1], st[m][len][1]) % Mod;
    };

    i64 ans = 0;
    if (k == 1) {
        ans = quiry(0, n);
    }
    else if (k == 2) {
        for (int i = 1; i < n; i++) {
            (ans += (quiry(0, i) + quiry(i, n)) % Mod) %= Mod;
        }
    }
    else {
        for (int len = 1; len + k - 1<= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int d = (i == 0 || i + len == n) ? 1 : 2;
                (ans += quiry(i, i + len) * C[n - len - d][k - 1 - d] % Mod) %= Mod;
            }
        }
    }
    std::cout << ans << '\n';
    return;
}
```
</details>

## I

相等判 YES，否则看有没有 0。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
bool solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    if (n == m) {
        return true;
    }
    else if (n == 0 || m == 0) {
        return false;
    }
    else {
        return true;
    }
}
```
</details>

## J

题目怎么说就怎么做

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    i64 ans = 0;
    int v = 0;
    for (auto &c : s) {
        if (c == '0') {
            v += 10;
            ans += v;
        }
        else if (c == '1') {
            v = std::max(0,  v - 5);
            ans += v;
        }
        else {
            ans += std::max(0, v - 10);
        }
    }
    std::cout << ans << '\n';
}
```
</details>

## K

**题目大意**

在平面上有若干个点，点 $x_i, y_i$ 对总价值的贡献是平面上存在的到该点距离为 $r_i$ 的点数量。求总价值。

**解题思路**

除了横或纵坐标相同的点外，还需要赵勾股数满足 $a^2 + b^2 = r_i^2$，于是先把所有的勾股数找到就好了。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
constexpr int N = 1e5, M = 2e5, Inf = 1e9, MXR = 3e5;

std::vector<std::array<int, 2>> R[MXR + 5];
std::unordered_set<int> mp[M + 5];

int ans;
void add(int x, int y) {
    if (x >= 0 && y >=0 && x <= M && y <= M && mp[x].count(y) != 0) {
        ans++;
    }
}

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

    int n = 0;
    std::cin >> n;
    std::vector p(n, std::array<int, 3>{});
    for (auto &[x, y, r] : p) {
        std::cin >> x >> y >> r;
        x += N, y += N;
        mp[x].insert(y);
    }

    for (auto &[x, y, r] : p) {
        if (r > MXR) {
            continue;
        }
        add(x + r, y);
        add(x - r, y);
        add(x, y + r);
        add(x, y - r);
        for (auto &[d1, d2] : R[r]) {
            add(x + d1, y + d2);
            add(x + d1, y - d2);
            add(x - d1, y + d2);
            add(x - d1, y - d2);
            add(x + d2, y + d1);
            add(x + d2, y - d1);
            add(x - d2, y + d1);
            add(x - d2, y - d1);
        }
    }
    std::cout << ans << '\n';
}
```
</details>

## L

构造。

我观察到的是从 1 开始以数 6 个为一组，每组可以产生两个符合条件的三元组。

当 $n$ 不为 3 且模 6 余 3 时，首尾处要特殊搞一下，但中间还是 6 个 6 个一组。

**CODE**

<details>
<summary>点击查看代码</summary>

```cpp
void solve()
{
    int n = 0;
    std::cin >> n;
    int ans = n / 6;
    if (n <= 3) {
        std::cout << 0 << '\n';
    }
    else if (n % 6 == 3) {
        std::cout << ans * 2 + 1 << '\n';
        std::cout << 1 << ' ' << 3 << ' ' << n << '\n';
        std::cout << 2 << ' ' << 4 << ' ' << 5 << '\n';
        std::cout << n - 1 << ' ' << n - 2 << ' ' << n - 3 << '\n';
        for (int i = 6; i < n - 3; i += 6) {
            std::cout << i << ' ' << i + 1 << ' ' << i + 3 << '\n';
            std::cout << i + 2 << ' ' << i + 4 << ' ' << i + 5 << '\n';
        }
    }
    else {
        int d = 0;
        if (n % 6 >= 4) {
            d = 1;
        }
        std::cout << ans * 2 + d << '\n';
        for (int i = 1; i < ans * 6; i += 6) {
            std::cout << i << ' ' << i + 1 << ' ' << i + 3 << '\n';
            std::cout << i + 2 << ' ' << i + 4 << ' ' << i + 5 << '\n';
        }
        if (d == 1) {
            int i = ans * 6 + 1;
            std::cout << i << ' ' << i + 1 << ' ' << i + 3 << '\n';
        }
    }
    return;
}
```
</details>

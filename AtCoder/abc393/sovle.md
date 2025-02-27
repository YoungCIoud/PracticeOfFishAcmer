## ABC

略

## D

**题目大意**

01串中有若干 1，求至少通过交换多少次相邻的数，能使得所有的 1 是连续的。

**解题思路**

我用的中位数定理，让全部的 1 往最中间的 1 靠，然后硬算交换了多少次。

但感觉 std 更加巧妙简单，以下是我对 std 的理解：

目标是通过交换让所有的 1 都连续，也就是 1 之间没有 0。于是考虑将 0 从 1 之间移出去，假设当前枚举到的 0 的左边有 $x$ 个 1，右边有 $y$ 个 1，那么不论左右两边的 1 是否连续，将这个 0 向左交换到第一个 1 的位置所需要的交换次数是 $x$，将这个 0 向右交换到最后一个 1 的位置所需要的交换次数是 $y$。两种方法都能使 0 交换到 1 外面，所以选交换次数最小的就好了。为什么不论是否连续？因为我们的每一次交换都应该交换 0 和 1。

（粘个用中位数定理写的）
<details>
<summary>CODE</summary>

```cpp
void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    std::vector<int> pos;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            pos.push_back(i);
        }
    }

    int mid = (pos.size() - 1) / 2;
    i64 ans = 0;
    for (int i = 0; i <= mid; i++) {
        ans += pos[mid] - pos[i];
    }
    for (int i = mid + 1; i < pos.size(); i++) {
        ans += pos[i] - pos[mid];
    }

    ans -= 1ll * mid * (mid + 1) / 2ll;
    ans -= 1ll * (pos.size() - mid - 1) * (pos.size() - mid) / 2ll;
    std::cout << ans << '\n';
}
```
</details>

## E

**题目大意**

有一个长度为 $n$ 的序列  $A$，对于每个 $i \in [1, n]$，求 $A$ 中包含 $A_i$ 的 $k$ 个数的 gcd 最大值是多少。

**解题思路**

假设包含 $A_i$ 的 $k$ 个数的 gcd 最大值是 $x$，则有以下两个必要条件：
1. $x | A_i$
2. $A$ 中至少有 $k$ 个数被 $x$ 整除

则对于每个 $A_i$ 我们可以取枚举它的因数，看满足条件 2. 的最大因数是多少，这个数就是我们要找的 $x$。

但是枚举因数太慢太麻烦了。注意到这题的数据量比一般的大，但是数据范围只有 $[1, 10^6]$。所以相对于枚举每个数的因数，我们可以从小到大枚举每个满足条件 2. 的倍数。

为了判断是否满足条件 2.，可以维护一个数组 $cnt[x]$，表示序列中有多少数是 $x$ 的倍数。暴力求就好了，复杂度含了一个调和序列。

<details>
<summary>CODE</summary>

```cpp
void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    int mx = 0;
    std::vector a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
        cnt[i]++;
        mx = std::max(mx, i);
    }
    for (int i = 1; i <= mx; i++) {
        for (int j = i + i; j <= mx; j += i) {
            cnt[i] += cnt[j];
        }
    }

    for (int i = 1; i <= mx; i++) {
        if (cnt[i] < k) {
            continue;
        }
        for (int j = i; j <= mx; j += i) {
            ans[j] = i;
        }
    }
    for (auto &i : a) {
        std::cout << ans[i] << '\n';
    }
    return;
}
```
</details>

## F

**题目大意**

有序列 $A$，记序列 $B[i] = {A_1, A_2,\dots , A_i}$。现在有 $q$ 个询问 $\{ R_i, x_i\}$ 表示 $B[R_i]$ 中最大值不超过 $x_i$ 的 LIS 的长度是多少。

**解题思路**

对于询问 $\{ R_i, x_i\}$ ，在不考虑从 $x_i$ 的情况下我们先用常规求 LIS 的方法求出 $B[R_i]$ 的 dp 数组，再在这个 dp 数组里二分找第一个大于 $x_i$ 的位置就好了。

显然不需要对每个 $B[R_i]$ 求一个 dp 数组，直接离线就好了。

<details>
<summary>CODE</summary>

```cpp
void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::vector a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::vector qr(n + 1, std::vector<std::array<int, 2>>{});
    for (int i = 0; i < q; i++) {
        int r = 0, x = 0;
        std::cin >> r >> x;
        qr[r].push_back({ x, i });
    }

    std::vector dp(n + 1, Inf + 5), ans(q, 0);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[std::lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin()] = a[i];
        for (auto &[mx, idx] : qr[i]) {
            ans[idx] = std::upper_bound(dp.begin(), dp.end(), mx) - dp.begin() - 1;
        }
    }

    for (auto &i : ans) {
        std::cout << i << '\n';
    }
    return;
}
```
</details>

## G

（看题解的篇幅就知道是做不了一点的题）
## 树的重心

### 定义

对于树上的一个节点， 删去它会将树分成若干子树， 记录这些子树节点数中的最大值。  
对树上的每个节点进行如上操作， 使得此最大值最小的节点就是数的重心。

### 性质

1. 一颗树最多存在两个重心， 且当有两个重心时， 这两个重心相邻。
2. 以树的重心为根时， 所有子树的大小不超过整棵树的一半。 这也意味着最大子树的大小小于等于其他子树大小的和。
3. 树上所有点到某一个点的距离和中， 到重心的距离和最小。
4. 把两棵树通过一条边相连得到一颗新的树， 则新树的重心在原来两颗树重心之间的路径上。

根据性质2. 可以很容易证明性质3. 。  
设所有 $n$ 个点到重心的距离和为 $d_0$， 当选定的点要从重心移动到相邻的点时， 最优选择肯定是往大小最大（设大小为 $mx$ ）的那颗子树移动， 这样一来， 移动后的距离和 $d_0 + (-mx) + (n - mx) = d_0 +  n - 2 * mx$ 一定不会比 $d_0$ 更小， 再从当前点往相邻的点移动最优一定是选则重心的。

### dfs求重心
```cpp
int dfs(int cur, int fa) {
    int siz = 1, mx = 0;
    for (auto &to : g[cur]) {
        if (to != fa) {
            int d = dfs(to, cur);
            siz += d;
            mx = std::max(mx, d);
        }
    }
    mx = std::max(mx, n - siz);
    if (mx < ans[1]) {
        ans = { cur, mx };
    }
    return siz;
}
```

## dus on tree （树上启发式合并）

### 模板题[Lomsat gelral](https://codeforces.com/contest/600/problem/E)

题目大意就是求出每个节点为根的子树里出现次数最多的颜色的编号和。

如果只对一颗子树求解， 我们只需要遍历子树下所有的点统计颜色计算答案就好了， 问题是统计完这颗子树后留下的信息会对计算它的兄弟子树造成影响， 所以还要撤销这颗子树留下的信息。 于是代码就可以这样写：

```cpp
void dfs(int cur, int fa) {
    for (auto &to : g[cur]) {
        if (to != fa) {
            dfs(to, cur);
            mx = 0, num = 0;
            undo(to, cur); // 撤销这颗子树的影响
        }
    }

    work(cur, fa); // 计算这颗子树的答案
    ans[cur] = num;
    
    return;
}
```

其中的 ``work()`` 就是遍历子树计算答案， ``undo()`` 就是在遍历子树撤销影响。  

显然以上实现的时间复杂度是 $O(n^2)$ 的, 接下来就是要考虑优化了。 ``undo()`` 函数的目的是为了撤销当前子树对下一棵要遍历的兄弟子树的影响， 那么当当前子树就是要遍历的最后一颗子树， 也就没必要撤销当前子树的影响了， 并且在计算父亲节点子树的答案时也可以跳过被保留的那颗子树， 显然当被保留的子树是节点数最多的子树（重儿子）时这种优化是最优的。 所以优化后的代码：

```cpp
void dfs(int cur, int fa) {
    for (auto &to : g[cur]) {
        // 跳过重儿子
        if (to != fa && to != h[cur]) {
            dfs(to, cur);
            mx = 0, num = 0;
            undo(to, cur);
        }
    }
    
    // 最后计算重儿子
    if (h[cur] != 0) {
        dfs(h[cur], cur);
    }

    // 遍历时跳过重儿子（因为上一步就已经计算了重儿子）
    work(cur, fa, h[cur]);
    ans[cur] = num;
    
    return;
}
```

接下来考虑时间复杂度。  
对于每个点， 他会被撤销当且仅当遍历到了该节点的是轻儿子的祖先。 而树链剖分有一个性质就是任意一个点到根节点的路径中轻边的数量不超过 $log_2n$。

> 从根往下每经过一条轻边所在子树的大小至少会除2

所以撤销操作的时间复杂度是 $O(nlogn)$ 。 类似的对某个节点计算答案的次数只用看从该节点到根的路径上经过了几条重链， 这个次数最大也是 $log2n$。  
所以总的时间复杂度就是 $O(nlogn)$ 。

再给出模版题的完整代码：
```cpp
constexpr int N = 1e5, M = 1e5, Inf = 1e9;
std::vector<int> g[N + 5], col(N + 5), cnt(N + 5);
std::vector<i64> ans(N + 5);
i64 num;
int mx;


std::vector<int> h(N + 5);
int init(int cur, int fa) {
    int siz = 1, m = 0;

    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        int n = init(to, cur);
        siz += n;
        if (n > m) {
            m = n;
            h[cur] = to;
        }
    }

    return siz;
}

void work(int cur, int fa, int s = 0) {
    int n = ++cnt[col[cur]];
    if (n == mx) {
        num += col[cur];
    }
    else if (n > mx) {
        num = col[cur];
        mx = n;
    }
    
    for (auto &to : g[cur]) {
        if (to != fa && to != s) {
            work(to, cur);
        }
    }
}
void undo(int cur, int fa) {
    cnt[col[cur]]--;
    for (auto &to : g[cur]) {
        if (to != fa) {
            undo(to, cur);
        }
    }
}

void dfs(int cur, int fa) {
    for (auto &to : g[cur]) {
        if (to != fa && to != h[cur]) {
            dfs(to, cur);
            mx = 0, num = 0;
            undo(to, cur);
        }
    }
    
    if (h[cur] != 0) {
        dfs(h[cur], cur);
    }

    work(cur, fa, h[cur]);
    ans[cur] = num;
    
    return;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> col[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    init(1, 0);
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << " \n"[i == n];
    }
    return;
}
```
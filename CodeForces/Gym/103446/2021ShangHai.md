## H.Life is a Game

### 题目大意
有一$n$个节点$m$条边的无向连通图，
每个节点有一个价值，
每一条边都有一个阈值。
对于某一条边，
你能通过这条边当且仅当你拥有的价值不小于这条边的阈值。

你初始在第$x$个节点拥有初始价值$k$，
你可以取得当前你所在节点的价值，
并且每个节点的价值只能取得一次。
初始时没有任何节点的价值被取得。

给定$q$个初始状态，
对于每个初始状态，问能取得的最大价值是多少。

### 题解1（启发式合并）

#### 思路

有几个很重要的观察就是：
1. 当你初始状态就不能跨过任何边时，该初始状态的答案就已经确定了。
2. 当你从一条阈值为w边到达节点x时，和x相连的阈值小于等与w的边一定可以被通过进而取得对面点的价值（第一次到达）。

首先我们考虑阈值最小的边(u, v, w)，
对于那些处于节点u或v的初始状态且不能通过这条边的，
那他就不能通过任何边了，
所以这些初始状态的答案就已经确定了（观察1）。  
剩下的处于节点u或v的初始状态就都是可以通过这条边取得对面节点的价值的。
并且对于后来经过任何边到达u的，
都可以经过这条最小的边到达v（v同理）。
这就相当于u和v已经是同一个点了。
所以我们考虑用并查集合并这两个点：
令``fa[u] = v``后``val[v] += val[u]``合并值，
同时所有在u上的初始状态都被合并到了v上。
所以我们启发式合并， 将状态少的合并到状态多的上。

对于所有的边从小到大依次进行上述操作后，
由于保证了图的连通性，
所以最后所有的点一定会被合并成一个点，
剩下未被确定答案的状态也就可以到所有的边。

#### CODE

```cpp
typedef std::array<int, 3> edge;
void solve()
{
    int n = 0, m = 0, q = 0;
    std::cin >> n >> m >> q;
    std::vector val(n, 0), ans(q, 0);
    for (auto &i : val) {
        std::cin >> i;
    }
    std::vector e(m, edge{});
    for (auto &[u, v, w] : e) {
        std::cin >> u >> v >> w;
        u--, v--;
    }
    std::sort(e.begin(), e.end(), [](edge u, edge v){
        return u[2] < v[2];
    });
    // 关于第x个点的询问, 记录初始值和id
    std::vector qr(n, std::multiset<std::array<int, 2>>{});
    for (int i = 0; i < q; i++) {
        int x = 0, k = 0;
        std::cin >> x >> k;
        qr[x - 1].insert({ k, i });
    }
    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }

    for (auto [u, v, w] : e) {
        u = getfa(u);
        v = getfa(v);
        if (u == v) {
            continue;
        }
        while (not qr[u].empty() && (*qr[u].begin())[0] + val[u] < w) {
            auto &[k, id] = *qr[u].begin();
            ans[id] = val[u] + k;
            qr[u].erase(qr[u].begin());
        } 
        while (not qr[v].empty() && (*qr[v].begin())[0] + val[v] < w) {
            auto &[k, id] = *qr[v].begin();
            ans[id] = val[v] + k;
            qr[v].erase(qr[v].begin());
        }

        if (qr[u].size() > qr[v].size()) {
            std::swap(u, v);
        }
        // 把u合并到v上
        while (not qr[u].empty()) {
            qr[v].insert(*qr[u].begin());
            qr[u].erase(qr[u].begin());
        }
        val[v] += val[u];
        fa[u] = v;
    }
    for (int i = 0; i < n; i++) {
        if (fa[i] == i) {
            for (auto &[k, id] : qr[i]) {
                ans[id] = k + val[i];
            }
        }
    }

    for (auto &i : ans) {
        std::cout << i << '\n';
    }
}
```

### 题解2（Kruskal重构树）

#### Kruskal 重构树

初始化一个森林，每个点单独是一棵树。
在运行 Kruskal 的过程中，
对于边权为 $w$ 的边 $(u, v)$ ，
令 u 所处的当前树的根节点是 fu ，
 v 的是 fv ，
则在森林中连 $(t, u)$ 和 $(t, v)$ ，
其中 $t$ 是新加入的点，
其点权为 $w$ 且作为新树的根。
若一开始有$n$个点，
则最后得到的重构树的根节点就是第 $(n + n - 1)$ 个点（有 $(n - 1)$ 条边会被分解所以新加入 $(n - 1)$ 个点）。

Kruskal 重构树有以下性质：  
1. 重构树是一颗二叉树，其叶子节点都是原图就有的点，剩下的都代表原图中的一条边（其点权就是边权）。
2. 按最小生成树建树，最后得到的树忽略叶子节点具有堆序性。
3. 按最小生成树建树，任意两节点所有路径中最大边权的最小值是它们重构树上 $LCA$ 的点权。

#### 思路

先建立重构树。
若我们现在在点 u ，
根据重构树的性质 2 我们可以取得以点 u 为根的子树下所有叶子的点权（价值）。
若我们想要上到点 u 的父亲节点 v 上，
我们就需要满足初值加上在 u 的子树里获得的价值的和大于等于 v 的点权（即原图中的边权）。
所以我们就可以得到能够从 u 到 v 的初态里最小的初值。
再用倍增的思路维护出能从 u 到某一祖先的初态里需要的最小初值。


#### CODE

```cpp
void solve()
{
    int n = 0, m = 0, q = 0;
    std::cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> val[i];
    }
    std::vector e(m, edge{});
    for (auto &[u, v, w] : e) {
        std::cin >> u >> v >> w;
    }
    std::sort(e.begin(), e.end(), [](edge u, edge v){
        return u[2] < v[2];
    });

    // kruskal 重构树
    for (int i = 1; i <= n * 2; i++) {
        fa[i] = i;
    }
    int cnt = 0;
    for (auto &[u, v, w] : e) {
        int fu = getfa(u);
        int fv = getfa(v);
        if (fu == fv) {
            continue;
        }

        cnt++;
        g[n + cnt].push_back(fu);
        g[n + cnt].push_back(fv);
        fa[fv] = fa[fu] = n + cnt;
        len[n + cnt] = w;
    }
    dfs(cnt + n);
    for (int i = 1; i < n + cnt; i++) {
        st[i][0][1] -= val[i];
    }
    for (int l = 1; l < 25; l++) {
        for (int i = 1; i + (1 << l) <= n + cnt; i++) {
            st[i][l][0] = st[st[i][l - 1][0]][l - 1][0];
            st[i][l][1] = std::max(st[i][l - 1][1], st[st[i][l - 1][0]][l - 1][1]);
        }
    }

    while (q--) {
        int x = 0, k = 0;
        std::cin >> x >> k;
        for (int l = 24; l >= 0; l--) {
            if (st[x][l][0] != 0 && k >= st[x][l][1]) {
                x = st[x][l][0];
            }
        }
        std::cout << val[x] + k << '\n';
    }
}
```

## J.Two Binary Strings Problem

### 题目大意

对于一个长为 $n$ 的01串 $S$，
定义 $f(l, r)$ 为该串的众数函数。
$f(l, r) = 1$ 当且仅当串 $S[l, r]$ 内 1 是众数（即 1 的数量严格大于 0 的数量。），
否则为 0 。

对于一个区间长度 $l$ ，
如果对于每个 $i$ 都有 $f(max(i - l + 1, 1), i) = T_i$( $T$ 也是01串)，
那么我们就说这个 $l$ 是合法的。

对于每个 $l \in[1, n]$，
依次判断是否合法，
合法输出1否则输出0，
最终会输出一个01串。

### 题解

#### 思路

大致思路就是对于每一个位置作为右端点，
我们都可以求出有哪些位置作为左端点是合法的，
进而求出有哪些区间长度是合法的，
最后输出1当且仅当该区间长度对于所有的位置都是合法的。

根据该思路，
对于每个右端点开一个``std::bitset``来记录合法的k，
最后他们相与就得到了我们想要的答案。

维护合法的左端点或者非法的左端点是等效的（因为它们互补）。
所以可以先直接维护出每个右端点众数为 1 的区间然后根据需要取反就好了。  
有一个很重要的预处理就是将所有的0替换成-1然后求前缀``pre[]``，
这样一来对于右端点 $r$ ，
就是要求所有的 $l$ 使得 $pre[r] - pre[l - 1] > 0$。

具体实现看代码注释。

#### CODE

```cpp
std::bitset<N + 5> ans, efc[N + 5], mk;
void init(int n) {
    for (int i = 1; i <= n; i++) {
        efc[i].reset();
    }
    ans.set();
    mk.set();
}

void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    init(n);
    std::vector<int> b(n + 1), pre(n + 1);
    for (int i = 1; i <= n; i++) {
        // scanf("%1d", &pre[i]);
        pre[i] = s[i - 1] - '0';
        if (pre[i] == 0) {
            pre[i] = -1;
        }
        pre[i] += pre[i - 1];
    }
    std::cin >> s;
    for (int i = 1; i <= n; i++) {
        b[i] = s[i - 1] - '0';
    }

    std::vector lst(n * 2 + 5, std::vector(0, 0));
    for (int i = n; i >= 1; i--) {
        lst[pre[i] + n].push_back(i);
    }
    auto pos = lst;
    pos[n].push_back(0);
    for (int i = 1; i <= n * 2; i++) {
        lst[i].push_back(0);
    }
    // 处理efc[i]: efc[i][j] = 1 表示pre[i] - pre[j - 1] > 0;
    for (int i = 1; i <= n; i++) {
        // 前缀值和当前值相同的上一个位置的结果可以直接继承过来
        efc[i] |= efc[lst[pre[i] + n].back()];
        // 更新lst，等找到以一个前缀值等于当前值的位置后，就可以找到现在这个位置。
        lst[pre[i] + n].pop_back();

        // 如果当前位置的前缀大于上一个位置的前缀
        // 那么上一个位置合法的对于当前位置也合法，继承过来就好了
        if (pre[i] > pre[i - 1]) {
            efc[i] |= efc[i - 1];
            while (not pos[pre[i - 1] + n].empty() && pos[pre[i - 1] + n].back() < i) {
                efc[i].set(pos[pre[i - 1] + n].back() + 1);
                pos[pre[i - 1] + n].pop_back();
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int val = efc[i][1];
        efc[i] <<= (n - i);
        mk.reset(n - i + 1);
        if (b[i] == 1) {
            if (val == 1) {
                efc[i] |= mk;
            }
        }
        else {
            efc[i].flip();
            if (val == 1) {
                efc[i] ^= mk;
            }
        }

        ans &= efc[i];
    }

    for (int i = n; i >= 1; i--) {
        std::cout << ans[i];
    }
    std::cout << '\n';
    return;
}
```
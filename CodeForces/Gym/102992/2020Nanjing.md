## D. Degree of Spanning Tree

### 题目大意

在一张有 $n$ 个节点的连通图中找一颗最大度不超过 $\lfloor \frac{n}{2} \rfloor$ 的生成树。

### 题解

#### 解题思路

首先任意构造一颗生成树。  
可以发现在有 $n$ 个节点的树中度数大于 $\lfloor \frac{n}{2} \rfloor$ 的节点最多只有一个。

如果没有直接输出答案就好了。
否则我们找到度数最大的点并以它为根，
尝试通过添加非树边并删去根和某儿子的边来减少根的度数并维持树的形态。
添加的非树边需要满足两端点的 LCA 是根节点，
这样根节点会在一个环上，
为了维持树形态必须删去一条与根相连且在环上的边。

还需要注意的是，
进行若干次添边删边操作的操作使根节点的度数 $\leq \lfloor \frac{n}{2} \rfloor$ 后，
可能会出现新的节点的度数又超过了 $\lfloor \frac{n}{2} \rfloor$ ，
并且可以证明如果有这样的节点那么它一定是根节点的儿子。

**Roughly Proof**  
考虑一朵有 $n + 2$ 个节点的大菊花（中心是 $u$ ）和 $n + 1$ 个节点的小菊花（中心是 $v$ ），
让它们共用一条边（这就构造了最临界的情况），
此时共有 $2n + 1$ 个节点且最大度的节点 $u$ 的度数为 $n + 1$ 显然大于 $\lfloor \frac{2n + 1}{2} \rfloor = n$ 。
此时需要删去一条与 $u$ 相连的边并添加一条不在树上的边。
最坏的情况就是删了一条非公共边并且添了一条与 $v$ 相连的边，
此时 $v$ 的度数变为 $n + 1$ 大于 $n$ 了。  
如果两个菊花图是共一个非中心的点，
那么此时共有 $2n + 2$ 个节点，这种最临界的情况就是题目所要求的树了。

这个问题的解决方法就是在进行增删操作之前，
判断一下此操作会不会产生新的不符合要求的节点，
会就跳过此次操作。

#### CODE
```cpp
std::vector<int> fa(N + 5, 0), g[N + 5];

int getfa(int u) {
    return fa[u] == u ? u : (fa[u] = getfa(fa[u]));
}

void dfs(int cur, int lst, int fst) {
    fa[cur] = fst;
    for (auto &to : g[cur]) {
        if (to != lst) {
            dfs(to, cur, fst);
        }
    }
    return;
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        g[i].clear();
    }

    std::vector<std::array<int, 2>> edge;
    while (m--) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        if (u == v) {
            continue;
        }
        if (u > v) {
            std::swap(u, v);
        }

        edge.push_back({ u, v });
    }
    std::sort(edge.begin(), edge.end());
    edge.erase(unique(edge.begin(), edge.end()), edge.end());
    m = edge.size();
    std::map<std::pair<int, int>, int> pos;
    std::vector deg(n + 1, 0);
    std::vector used(m, false);
    for (int i = 0; i < m; i++) {
        auto &[u, v] = edge[i];
        pos[{ u, v }] = pos[{ v, u }] = i;
        int fu = getfa(u), fv = getfa(v);
        if (fu != fv) {
            g[u].push_back(v);
            g[v].push_back(u);
            deg[u]++, deg[v]++;
            fa[fu] = fv;
            used[i] = true;
        }
    }

    int rt = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] * 2 > n) {
            rt = i;
            break;
        }
    }
    if (rt != 0) {
        fa[rt] = rt;
        for (auto &to : g[rt]) {
            dfs(to, rt, to);
        }

        for (int i = 0; i < m && deg[rt] * 2 > n; i++) {
            if (used[i]) {
                continue;
            }

            auto &[u, v] = edge[i];
            int fu = getfa(u), fv = getfa(v);
            if (fu == fv || u == rt || v == rt) {
                continue;
            }

            bool ok = false;
            deg[u]++, deg[v]++;
            if (not ok) { // 尝试删除 rt - fu
                deg[fu]--;
                if (deg[fu] * 2 <= n && deg[fv] * 2 <= n) {
                    used[pos[{ fu, rt }]] = false;
                    ok = true;
                    fa[fu] = fv;
                }
                else {
                    deg[fu]++;
                }
            }
            if (not ok) { // 尝试删除 rt - fv
                deg[fv]--;
                if (deg[fu] * 2 <= n && deg[fv] * 2 <= n) {
                    used[pos[{ fv, rt }]] = false;
                    ok = true;
                    fa[fv] = fu;
                }
                else {
                    deg[fv]++;
                }
            }

            if (ok) {
                deg[rt]--;
                used[i] = true;
            }
            else {
                deg[u]--, deg[v]--;
            }
        }
    }

    if (deg[rt] * 2 <= n) {
        std::cout << "Yes\n";
        for (int i = 0; i < m; i++) {
            if (used[i]) {
                std::cout << edge[i][0] << ' ' << edge[i][1] << '\n';
            }
        }
    }
    else {
        std::cout << "No\n";
    }
    return;
}
```

## J. Just Another Game of Stones

### 题目大意

给你 $n$ 堆石子和 $q$ 次操作如下二选一的操作：
1. ``1 l r x``：将区间 $[l, r]$ 中石子数小于 $x$ 的堆的石子增加为 $x$ 。
2. ``2 l r x``；用区间 $[l, r]$ 中的石子堆额外加一堆含有 $x$ 个石子的堆进行取石子的游戏， 求先手第一步有多少种不同的取法保证必赢。

### 题解

#### 解题思路

都知道取石子游戏里先手必胜的条件是所有石子堆石子数的异或和（ $sum$ ）不为 0 ，
在此种情况下，
先手想赢就必须在某堆中取出若干石子，
使得留给后手的石子堆的异或和为 0 。  
假设我们想要从有 $x$ 个石子的堆中取石子，
那么就要取 $sum \oplus x$ 个，
显然合法的情况是 $sum \oplus x \leq x$。

那么满足什么性质的 $x$ 能够满足如上不等式呢？  
（~~惊人注意力或常见数学得~~）答案是当且仅当 $sum$ 二进制表示中出现了 1 的最高位在 $x$ 中也是 1 。

所以我们的任务就是维护区间异或、某一位在该区间中有多少数是 1 和区间更新较小值。

这就要用到线段树加上 segment tree beats 的技巧。

#### [segment tree beats](https://www.cnblogs.com/trsins/p/17970751)

该方法主要用于区间内所有的数对 $x$ 取最值。  
以取最大值为例，
我们对每个区间维护最小值 $mn$ 、次小值 $se$ （初始化为正无穷）。
当要用 $x$ 更新某一区间时，
分三种情况考虑：
1. $x \leq mn$ 时直接返回；
2. $mn < x < se$ 时只需要更新该区间内的最小值；
3. $se \leq x$ 时继续向下更新左右儿子。

再根据题目要求，
去维护别的量。

#### CODE
```cpp
constexpr u32 Inf = 1 << 30;
struct Node {
    u32 mn, cnt, se; // 最小值 最小值的个数 次小值
    u32 sum; // 异或和
    std::vector<u32> tot; // 某一位为 1 的数的个数
    u32 tag;
    Node(u32 num = Inf) {
        mn = num;
        cnt = 1;
        se = Inf;
        sum = num;
        tag = Inf;

        tot.assign(30, 0);
        for (int i = 0; i < 30; i++) {
            if (num >> i & 1) {
                tot[i] = 1;
            }
        }
    }

    Node operator+ (const Node &a) {
        Node tmp;
        if (mn == a.mn) {
            tmp.mn = mn;
            tmp.cnt = cnt + a.cnt;
            tmp.se = (se < a.se) ? se : a.se;
        }
        else if (a.mn < mn) {
            tmp.mn = a.mn;
            tmp.cnt = a.cnt;
            tmp.se = (mn < a.se) ? mn : a.se;
        }
        else {
            tmp.mn = mn;
            tmp.cnt = cnt;
            tmp.se = (se < a.mn) ? se : a.mn;
        }
        
        tmp.sum = a.sum ^ sum;
        for (int i = 0; i < 30; i++) {
            tmp.tot[i] = a.tot[i] + tot[i];
        }
        return tmp;
    }
} tr[N * 4];
u32 a[N + 5];

void push_up(int cur) {
    tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
}
void make_tag(int cur, int tg) {
    if (tg <= tr[cur].mn) {
        return;
    }
    auto &[mn, cnt, se, sum, tot, tag] = tr[cur];
    tag = tg;
    for (int i = 0; i < 30; i++) {
        if (mn >> i & 1) {
            tot[i] -= cnt;
        }
        if (tg >> i & 1) {
            tot[i] += cnt;
        }
    }

    if (cnt & 1) {
        sum ^= (mn ^ tg);
    }
    mn = tg;
    return;
}
void push_down(int cur) {
    if(tr[cur].tag == Inf) {
        return;
    }
    make_tag(cur << 1, tr[cur].tag);
    make_tag(cur << 1 | 1, tr[cur].tag);
    tr[cur].tag = Inf;
}
void build(int cur, int l, int r) {
    if (l == r) {
        tr[cur] = Node(a[l]);
        return;
    }
    int m = l + r >> 1;
    build (cur << 1, l, m);
    build (cur << 1 | 1, m + 1, r);
    push_up(cur);
}
void upd(int cur, int l, int r, int ls, int rs, u32 x) {
    // 区间最小值比x大，直接返回
    if (tr[cur].mn >= x) {
        return;
    }
    // x 属于 (mn, se)， 直接更新mn
    if (ls <= l && r <= rs && tr[cur].se > x) {
        make_tag(cur, x);
        return;
    }

    int m = l + r >> 1;
    push_down(cur);
    if (m >= ls) {
        upd(cur << 1, l, m, ls, rs, x);
    }
    if (m < rs) {
        upd(cur << 1 | 1, m + 1, r, ls, rs, x);
    }
    push_up(cur);
    return;

}
Node quiry(int cur, int l, int r, int ls, int rs) {
    if (ls <= l && r <= rs) {
        return tr[cur];
    }

    push_down(cur);
    int mid = l + r >> 1;
    if (rs <= mid) {
        return quiry(cur << 1, l, mid, ls, rs);
    }
    else if (mid < ls) {
        return quiry(cur << 1 | 1, mid + 1, r, ls, rs);
    }
    else {
        return quiry(cur << 1, l, mid, ls, rs) + quiry(cur << 1 | 1, mid + 1, r, ls, rs);
    }
}


void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    build(1, 1, n);
    while (q--) {
        u32 ope = 0, l = 0, r = 0, x = 0;
        std::cin >> ope >> l >> r >> x;
        if (ope == 1) {
            upd(1, 1, n, l, r, x);
        }
        else {
            auto res = quiry(1, 1, n, l, r);
            res.sum ^= x;
            int p = -1;
            for (int i = 0; i < 30; i++) {
                if (res.sum >> i & 1) {
                    p = i;
                }
            }
            std::cout << (~p ? (res.tot[p] + (x >> p & 1)) : 0) << '\n';
        }
    }
}
```
## H. Line Graph Matchings

### 题目大意

找到一张连通、无自环、无重边的图的[线图](https://zhuanlan.zhihu.com/p/420704461)的最大权值匹配。

### 题解（割边，思维）

#### 思路

首先有一个非常重要的观察：
在线图中选一条边所产生的权值就是原图中对应的两条边的权值，
在线图中的两条边不相邻就是原图中的这两条边对应的四条边不重合。
于是问题就转换成了在原图中不重复地选相邻的两条边并取得他们的权值问能取得的最大权值是多少。

对于有偶数条边的一定能将所有的边选到，考虑归纳法：
```
对于只有两条边的图，直接将两条边选掉就完了。
对于边数为偶数且大于2的图，
如果存在非割边，那非割边的数量一定大于2（成环），
选两条后仍保证图是连通的且有偶数条边，所以能够选完；
如果所有的边都是割边，那图就是一颗树，从叶子往上选两条就好了。
综上，有偶数条边的图一定能选完。
```
此时直接求和输出答案就好了。

对于奇数条边的图，有一条边不能被选到。
如果这条边是非割边，忽略掉后图仍连通且有偶数条边，这些边就可以全选了。
如果这条边是割边，忽略掉后图就变成了两个连通块，如果两个连通块里都有奇数条边，那忽略掉这条边肯定不是最优的。如果两个连通块里都有偶数条边，就可以全选了。  
所以我们只用找最小且忽略掉该边后连通块中仍是偶数条边的边的最小权值。

#### CODE
```cpp
int n, m;
std::vector<std::array<int, 2>> g[N + 5];
std::vector<i64> w(M + 5);
std::vector<bool> vis(M + 5);

std::vector<int> dfn(N + 5), low(N + 5), num(N + 5), e(M + 5);
int tim;
void dfs(int cur, int fa = 0) {
	tim++;
	dfn[cur] = tim;
	low[cur] = tim;
	int eid = M;
	for (auto &[to, id] : g[cur]) {
		if (to == fa) {
			eid = id;
			continue;
		}
		if (not vis[id]) {
			vis[id] = true;
			num[cur]++;
		}
		
		if (dfn[to]) {
			low[cur] = std::min(low[cur], dfn[to]);
		}
		else {
			dfs(to, cur);
			num[cur] += num[to];
			low[cur] = std::min(low[cur], low[to]);
		}
	}
	
	if (dfn[cur] <= low[cur]) {
		// 当前节点跟父亲节点的连边是一条割边 
		e[eid] = num[cur];
	}
	return;
}

int main() {
	std::cin >> n >> m;
	i64 ans = 0;
	for (int i = 0; i < m; i++) {
		int u = 0, v = 0;
		std::cin >> u >> v >> w[i];
		ans += w[i];
		g[u].push_back({ v, i });
		g[v].push_back({ u, i });
	}
	
	i64 mn = 0;
	if (m & 1) {
		dfs(1);
		mn = Inf;
		for (int i = 0; i < m; i++) {
			// e[i] 把第i条边忽略掉后形成的两个块中其中一块边的数量 
			if (e[i] % 2 == 0) {
				mn = std::min(mn, w[i]);
			}
		}
	}
	
	std::cout << ans - mn << '\n';
	return 0;
}
```

## L. Perfect Matchings

### 题目大意

在一张有 $2n$ 个节点的完全图中删去 $2n - 1$ 条边且这些边构成一颗树，
求删去边后的图上完美匹配的方案数。

### 题解（容斥）

#### 思路

首先对于任意有 $2n$ 个节点的完全图，
我们可以根据以下公式得到方案数：

$$
f(n) =\frac{C_{2n}^{n}n!}{2^n}
$$

其意义是：
先将 2n 个节点分成两部分，
通过固定一部分找另一部分的全排列就可以进行两两匹配，
又因为 $(u, v)$ 与 $(v, u)$ 是等价的，
所以还要2的幂来去重。

稍微推一推可以发现 $f(n)$ 可以递推出来：
$$
f(n) = (2n - 1)f(n - 1);
$$

我们要求的答案就是总的方案数 $f(n)$ 减去匹配中包含树边的方案数。
所以接下来要求的就是匹配中包含树边的方案数。

设包含第 $i$ 条树边的约束为
拥有约束 $P_i$ 的匹配方案构成集合 $S_i$ ，
我们要求的匹配中包含树边的方案数就是：
$$
|\bigcup_{i = 1}^{2n-1} S_i |
$$
由容斥原理，上式可以如下计算：
$$
|\bigcup_{i = 1}^{2n-1} S_i | =
\sum_{m = 1}^{n}(-1)^{m - 1}\sum_{a_i < a_{i+1}}|\bigcap_{i=1}^{m}S_{a_i}|
$$

上式中 m 就是同时满足多少约束条件，
因为要求的是完美匹配，
所以在树中最多同时满足 n 个约束条件。

然后问题就来到了如何求同时满足 m 个约束条件的方案数（我们只关心方案数而并不关心具体有那些方案）。
为了解决这个问题，
有一个非常重要且大大简化代码的等价关系：
满足某一个约束条件 即 钦定了某一条边 即 将该边的两个顶点匹配了。

对边计算难度是远大于对点计算的。
所以满足 $m$ 个约束条件的方案数就是有 $m$ 对点匹配且没有点重复的方案数。
于是设计 $dp[i][j][0/1]$ 表示在点 $i$ 的子树下，
已经匹配了 $j$ 对点，
且点 $i$ 还未被匹配或已经被匹配的方案数。
并且有如下转移：
$$
dp[cur][i + j][0] = dp[cur][i][0] \times (dp[to][j][0] + dp[to][j][1])\\
dp[cur][i + j][1] = dp[cur][i][1] \times (dp[to][j][0] + dp[to][j][1])\\
dp[cur][i + j + 1][1] = dp[cur][i][0] \times dp[to][j][0]\\
(cur 就是当前节点， to 就是当前节点的子节点)
$$
第三个转移就是在当前节点和一个儿子节点之间新建一个匹配。

#### CODE
```cpp
i64 f[N + 5];
std::vector<int> g[N * 2 + 5];
// dp[i][j][0/1] : i的子树下，匹配了j对点，且i点有没有被匹配的方案数
i64 dp[N * 2 + 5][N * 2 + 5][2];
int siz[N * 2 + 5]; // siz[i] : i的子树共有多少个节点

void dfs(int cur, int fa = 0) {
    dp[cur][0][0] = 1ll;
    siz[cur] = 1;
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        dfs(to, cur);
        for (int i = siz[cur] / 2; i >= 0; i--) {
            for (int j = siz[to] / 2; j >= 0; j--) {
                if (j > 0) {
                    (dp[cur][i + j][0] += dp[cur][i][0] * (dp[to][j][0] + dp[to][j][1]) % Mod) %= Mod;
                    (dp[cur][i + j][1] += dp[cur][i][1] * (dp[to][j][0] + dp[to][j][1]) % Mod) %= Mod;
                }
                // cur 和 to 之间新建匹配
                (dp[cur][i + j + 1][1] += dp[cur][i][0] * dp[to][j][0] % Mod) %= Mod;
            }
        }
        siz[cur] += siz[to];
    }
    return;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i < 2 * n; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = (f[i - 1] * (2ll * i - 1)) % Mod;
    }

    dfs(1);
    i64 ans = f[n];
    for (int i = 1; i <= n; i++) {
        if (i & 1) {
            (ans -= (dp[1][i][0] + dp[1][i][1]) * f[n - i] % Mod) %= Mod;
        }
        else {
            (ans += (dp[1][i][0] + dp[1][i][1]) * f[n - i] % Mod) %= Mod;
        }
    }
    std::cout << (ans + Mod) % Mod << '\n';
}
```

这个 ``void dfs(int, int)`` 的实现咋一看像是 $O(n^3)$ 的，
其实复杂度相当于在 $LCA$ 统计点对。
$dfs$ 一遍后每个点都与其他点匹配了一次，
所以是 $O(n^2)$ 的。

## M. String Problem

### 题目大意

给出一个串，
对该串的每个前缀求字典序最大的子串，
只需要输出求得字串得左端点下标和右端点。

### 题解（KMP？）

#### 解题思路

显然右端点在当前串最的右边，
所以问的就是对于一个串，
我在串尾插入一个字符后，
串的最大字串的左端点会转移到哪里？  
假设我已经知道了当前串的最大子串的位置，
对于将插入的字符，
如果它大于当前最大字串的第一个字符，
那么插入后的最大子串就是该字符自己。


对于其他情况就要进行特殊考虑，
即使插入一个比最大字串开头字符小的字符答案也可能发生改变（比如 ``tacta + d`` ）。
这种情况发生的前提是当前串串长大于 1 且存后缀跟最大子串的前缀重合。  
将最大子串左端点的下标记为 $head$ ，
长度记为 $len$，
并且记 $l[len]$ 当长度为 $len$ 时与最大字串前缀匹配的最长后缀。
那么对于将要新加进来的字符，
我们就先拿它与下标为 $head + l[len]$ 的字符比较，
若大于 $head$ 就要移动到 $head + len - l[len]$ 的位置而长度更新为 $l[len]$。
完成一次更新后得到的串就是原最大子串长度为 $l[len]$ 的前缀，
将该串继续按照上述方式更新就好了。

#### CODE

```c++
void solve()
{
    std::string s;
    std::cin >> s;
    int n = s.length();
    std::vector nxt(n + 1, 0);
    s = "#" + s;
    std::cout << 1 << ' ' << 1 << '\n';
    int head = 1, len = 1;
    for (int i = 2; i <= n; i++) {
        if (s[i] > s[head]) {
            head = i, len = 1;
            std::cout << i << ' ' << i << '\n';
            continue;
        }

        while (s[head + nxt[len]] < s[i]) {
            head = head + len - nxt[len];
            len = nxt[len];
        }
        if (s[head + nxt[len]] == s[i]) {
            nxt[len + 1] = nxt[len] + 1;
            len++;
        }
        else if (s[head + nxt[len]] > s[i]) {
            nxt[++len] = 0;
        }
        std::cout << head << ' ' << i << '\n';
    }
    return;
}
```
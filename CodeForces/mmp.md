# Miao Maio Problem（喵喵题）

## [Alice's Adventures in Addition](https://codeforces.com/contest/2028/problem/F)（dp的优化 bitset）

### 题解（题意见链接）

#### 解题思路

我们可以先想出非常 naive 的 dp：
$dp[i][j] = 0 / 1$ 表示在前 $i$ 个数里插入运算符后的结果能否是 $j$。

于是当 $a_i = 0$ 时我们有如下转移：
$$
dp[i][j] = dp[0][j] \mid dp[1][j] \mid \dots \mid dp[i - 1][j]
$$
因为通过末尾 0 能通过乘法将一段后缀乘成 0，
所以能取到前缀能达到的所有值。  
当 $a_i = 1$ 时：
$$
dp[i][j] = dp[i - 1][j] | dp[i - 1][j - 1]
$$
既在前面的式子后乘一或加一。  
当 $a_i >= 2$ 时，
从 $a_i$ 开始在遇到 0 之前可以一直往前连乘，
设乘到 $a_j$ 连乘得结果是 $prd_j(prd_i = a_i)$， 则：
$$
dp[i][j] = dp[i - 1][j - prd_i] \mid dp[j][j - prd_j] \mid \dots
$$
当遇到第一个（从后往前） $a_k = 0$ 时还有：
$$
dp[i][j] \mid = dp[k][j]
$$
因为连乘到 $a_k$ 时后面一段得结果就变成了 0，
相当于对 $a_k = 0$ 进行转移，
结果已经计算过了就是 $dp[k]$

这样转移的时间复杂度瓶颈在于 $a_i >= 2$ 时枚举连乘（其他所有转移都可以是 $O(1) 的$），
最坏的情况下单次转移可以达到 $O(n)$。  
显然空间复杂度也是不达标的。

$2^{14} > 10^4$ 表明对于大于等于 2 的数最多能连乘 13 次，
再乘下去就超过了给定的 $m$ 是无意义的。
但是在连乘时会出现许多 1 导致连乘次数大于 13。
所以 我们考虑跳过这些 1， 
只关心非 1 非 0 的位置，
这样单次转移最多就是 13 次。

但是$O(13nm)$的复杂仍过不了，
可以通过 bitset 的移位加快第二维的转移，
具体实现看代码。

#### CODE

```cpp
std::deque<std::pair<int, std::bitset<M + 1>>> q; // 非 0 非 1
std::bitset<M + 1> all; // 记录当前为止所有出现过的数
std::bitset<M + 1> cur; // 当前状态
std::bitset<M + 1> lst; // 上一个的状态
std::bitset<M + 1> zero; // 开头到目前为止最后一个0的状态
void init() {
    q.clear();
    all = 1;
    lst = 1;
    zero = 0;
}

void solve()
{
    init();
    int n = 0, m = 0;
    std::cin >> n >> m;
    while (n--) {
        int a = 0;
        std::cin >> a;

        if (a == 0) {
            cur = zero = all;
            q.clear();
        }
        else if (a == 1) {
            cur = lst | (lst << 1);
        }
        else {
            cur = zero;
            q.push_front({ a, lst });
            for (int i = 0, prd = q[i].first; prd <= m; prd *= q[++i].first) {
                cur |= (q[i].second << prd);
                if (i == q.size() - 1) {
                    break;
                }
            }
            while (q.size() >= L) {
                q.pop_back();
            }
        }
        
        lst = cur;
        all |= cur;
    }
    std::cout << (cur[m] ? "Yes" : "No") << '\n';
}
```
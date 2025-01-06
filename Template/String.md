## 前缀数组KMP
```cpp
namespace KMP
{
    // 获取前缀数组
    std::vector<int> get_prefix(std::string s)
    {
        int len = s.length();
        std::vector<int> pi(len);
        for (int i = 1; i < len; i++)
        {
            int j = pi[i - 1];
            while (j && s[i] != s[j])
                j = pi[j - 1];
            if (s[i] == s[j])
                j++;
            pi[i] = j;
        }
        return pi;
    }
    // 返回文本串中模式串第一个出现的位置， 无则返回-1
    int find_first(std::string pattern, std::string text)
    {
        auto pi = get_prefix(pattern);
        for (int i = 0, j = 0; i < text.length(); i++)
        {
            while (j && text[i] != pattern[j])
                j = pi[j - 1];
            if (text[i] == pattern[j])
                j++;
            if (j == pattern.length())
                return i - j + 1;
        }
        return -1;
    }
    // 返回模式串在文本串中的所有出现
    std::vector<int> find_all(std::string pattern, std::string text)
    {
        std::string tem = pattern + "#" + text;
        std::vector<int> pi = get_prefix(tem), ans;
    
        for (int i = pattern.length() + 1; i < tem.length(); i++)
            if (pi[i] == pattern.length())
                ans.push_back(i - pattern.length() * 2);
        return ans;
    }
}
```

## AC自动机 多模式串匹配

fail指针指向所有模式串的前置中,能够匹配**当前状态后缀**的最长前缀.

### easy
```c++
// insert入所有的模式串后build
constexpr int len = 1e6;
namespace AC
{
    int tr[len + 5][26], cnt = 1;
    int fail[len + 5], e[len + 5];

    void insert(std::string s)
    {
        int cur = 0;
        for (auto c : s)
        {
            if (!tr[cur][c - 'a'])
                tr[cur][c - 'a'] = cnt++;
            cur = tr[cur][c - 'a'];
        }
        e[cur]++;
    }

    void build()
    {
        std::queue<int> q;
        for (int i = 0; i < 26; i++)
            if (tr[0][i])
                q.push(tr[0][i]);
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < 26; i++)
            {
                if (tr[cur][i])
                    fail[tr[cur][i]] = tr[fail[cur]][i],
                    q.push(tr[cur][i]);
                else
                    // 从当前状态,跳转到次态的后缀(修改了字典树的形态)
                    tr[cur][i] = tr[fail[cur]][i];
            }
        }
    }

    // 查询模式串一共在s中出现了多少次
    int quiry(std::string s)
    {
        int cur = 0, ans = 0;
        for (auto c : s)
        {
            cur = tr[cur][c - 'a'];
            for (int i = cur; i && ~e[i]; i = fail[i])
                ans += e[i], e[i] = -1;
        }
        return ans;
    }
};
```
### plus
查询每个模式串在文本串中出现了多少次
```c++
constexpr int MaxT = 2e6, N = 2e5, MaxS = 2e5;
int cnt[N + 5];
namespace AC
{
    struct Node
    {
        int nex[26] = {};
        int fail = 0;
        vct<int> idx {};

        int val = 0;
    }node[MaxS + 5];
    int root = 0, tot = 1;

    void insert(str s, int idx)
    {
        int cur = root;
        for (auto& c : s)
        {
            if (node[cur].nex[c - 'a'] == 0)
                node[cur].nex[c - 'a'] = tot++;
            cur = node[cur].nex[c - 'a'];
        }
        node[cur].idx.push_back(idx);
    }

    void build()
    {
        std::queue<int> q;
        for (int i = 0; i < 26; i++)
            if (node[root].nex[i])
                q.push(node[root].nex[i]);
        
        while (!q.empty())
        {
            int cur = q.front();
            auto& t = node[cur];
            q.pop();

            for (int i = 0; i < 26; i++)
            {
                if (t.nex[i])
                {
                    node[t.nex[i]].fail = node[t.fail].nex[i];
                    q.push(t.nex[i]);
                }
                else
                {
                    t.nex[i] = node[t.fail].nex[i];
                }
            }
        }
        return;
    }

    // 记录每个节点访问到了多少次
    void quiry(str s)
    {
        int cur = root;
        for (auto& c : s)
        {
            cur = node[cur].nex[c - 'a'];
            node[cur].val++;
        }
        return;
    }

    // 所有fail失配指针构成一颗树
    // 此处用链式前向星建图, 用vector也是可以的
    int head[MaxS + 5], nex[MaxS + 5], to[MaxS + 5];
    int num = 1;
    
    void add(int u, int v)
    {
        nex[num] = head[u], to[num] = v;
        head[u] = num++;
    }

    int dfs(int cur)
    {
        auto& t = node[cur];
        for (int e = head[cur]; e; e = nex[e])
            t.val += dfs(to[e]);

        for (auto& i : t.idx)
            cnt[i] += t.val;

        return t.val;
    }

    void failtree()
    {
        for (int i = 1; i < tot; i++)
            add(node[i].fail, i);

        dfs(root);
    }
};
```

## 字符串哈希
```c++
struct Hash
{
    const i64 P = 1e12 + 39;
    const int B = 13331;
    std::vector<i64> h, p;
    Hash(std::string s) : h(s.size() + 1), p(s.size() + 1) {
        int n = s.size();
        p[0] = 1;
        for (int i = 0; i < n; i++) {
            h[i + 1] = (h[i] * B + s[i]) % P;
            p[i + 1] = p[i] * B % P;
        }
    }

    //左闭右开 从 0 开始, 返回字串的哈希值
    i64 get(int l, int r) {
        return (h[r] + __int128(h[l]) * (P - p[r - l])) % P;
    }
};
```

## 倍增求后缀数组
// 以下代码能够求包含大小写字母和数字的字符串的后缀数组, 且按照ASCII码大小排序
```c++
std::vector<int> get(std::string &s, int n) {
    std::vector<int> sa(n, 0), rk(n * 2, 0), tmp(n * 2, 0), cnt(n + 'z', 0);
    // init
    for (int i = 0; i < n; i++) {
        cnt[s[i]]++;
    }
    for (int i = 1; i <= 'z'; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        sa[--cnt[s[i]]] = i;
    }
    rk[sa[0]] = 1;
    for (int i = 1, p = 1; i < n; i++) {
        rk[sa[i]] = (s[sa[i]] == s[sa[i - 1]] ? p : ++p);
    }

    // a -> b
    auto trans = [&](std::vector<int> &a, std::vector<int> &b, int d) -> void {
        std::fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; i++) {
            cnt[rk[i + d]]++;
        }
        for (int i = 1; i <= n; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            b[--cnt[rk[a[i] + d]]] = a[i];
        }
    };
    for (int k = 1; k < n; k <<= 1) {
        trans(sa, tmp, k), trans(tmp, sa, 0);

        tmp[sa[0]] = 1;
        for (int i = 1, p = 1; i < n; i++) {
            if (rk[sa[i]] > rk[sa[i - 1]] || rk[sa[i] + k] > rk[sa[i - 1] + k]) {
                p++;
            }
            tmp[sa[i]] = p;
        }
        rk = tmp;
    }
    return sa;
}
```

## 回文自动机PAM

回文自动机中每个节点的状态表示一个回文子串，为了区分奇长和偶长的回文串，回文自动机中还有奇根和偶根。

回文自动机中的 ``fail[]`` 指向的是当前状态代表的回文子串除自身外最长的回文子串。
```cpp
// u 是PAM中状态的编号
// len是当前状态对应回文子串的长度
int tr[N][26];
int len[N], fail[N], tot = 1;
std::string s;
int getfail(int u, int i) {
    while (i - len[u] - 1 < 0 || s[i - len[u] - 1] != s[i]) {
        u = fail[u];
    }
    return u;
}

int main () {
    fail[0] = 1;
    len[1] = -1;
    std::cin >> s;
    for (int i = 0, now = 0; i < s.length(); i++) {
        int c = s[i] - 'a';
        int pos = getfail(now, i);
        if (tr[pos][c] == 0) {
            fail[++tot] = tr[getfail(fail[pos], i)][c];
            tr[pos][c] = tot, len[tot] = len[pos] + 2;
        }
        now = tr[pos][c];
    }
}
```

## Z 函数/拓展KMP

**约定**

字符串的下标都是以 0 开头。

**定义**

对于一个长度为 $n$ 的字符串 $s$， 定义函数 $z[i]$ 表示最长的 $l$ 使得 $s[0,l - 1] = s[i, i + l - 1]$ （$s[l, r]$ 表示以第 $l$ 个字符开头第 $r$ 个字符结尾的子串）。

**朴素算法**

由定义很容易想到用两个简单的循环就可以得到 $z[i]$ 了。

**线性算法**

从左往右遍历，对于每一个已经遍历到的 $i$ 我们都可以得到一个子串 $s[i, i + z[i] - 1]$，我们维护所有已经遍历到的子串中右边界最大的那个，将两个边界记为 $l$ 和 $r$，则在求解下一个位置 $x$ 的 Z 函数值时，就可以分两种情况来讨论：  
1. $x \leq r$，即所维护子串的右边界比 x 大，此时有 $s[x, r] = s[x - l, r - l]$，这时我们就有了 $z[x]$ 的下界： $z[x] = min(z[x - l], r - x + 1)$。此后又分两种情况讨论：  
    1. $z[x - l] < r - i + 1$，此时直接令 $z[x] = z[x - l]$ 就好了。
    2. 否则先令 $z[x] = r - x + 1$，然后按照朴素算法向后拓展。
2. 否则就按朴素算法向后拓展

可以发现 2. 和 1.ii 是可以合并的。

```cpp
std::vector<int> zfun(std::string s) {
    int n = s.length();
    std::vector z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r && z[i - l] < r - i + 1) {
            z[i] = z[i - l];
        }
        else {
            z[i] = std::max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}
```

内层循环每次都会让右边界增大，最多增大 $n$ 次，所以总的来说这种实现方式是线性的。
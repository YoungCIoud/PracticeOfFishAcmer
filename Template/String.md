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
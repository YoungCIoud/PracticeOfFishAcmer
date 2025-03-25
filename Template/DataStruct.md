## 对顶堆

对顶堆由一个大根堆和小根堆组成, 能够**动态**维护第k大的值或中位数.

对顶堆能够由优先队列或着多重集实现, 只不过后者能够更方便的进行删除元素.

下面给出维护中位数的例子:
```cpp
class mset
{
public:
    // 初始时插入正负无穷
    void init()
    {
        less.clear(), greater.clear();
        less.insert(-Inf), greater.insert(Inf);
        less_sum = 0, greater_sum = 0;
    }
    void insert(int val)
    {
        if (val < *greater.begin()) less.insert(val), less_sum += val;
        else greater.insert(val), greater_sum += val;

        adjust(); 
    }
    void erase(int val)
    {
        if (val < *greater.begin()) less.erase(less.lower_bound(val)), less_sum -= val;
        else greater.erase(greater.lower_bound(val)), greater_sum -= val;

        adjust();
    }
    int get()
    {
        // 求中位数要考虑元素总个数的奇偶
        int m = 0;
        int d = less.size() - greater.size();

        if (d)
            m = *less.begin();
        else
            m = *less.begin() + *greater.begin() >> 1;
        
        return m;
    }
private:
    std::multiset<int, std::greater<int>> less;
    std::multiset<int> greater;
    i64 less_sum, greater_sum; // 根据题目要求而加

    void adjust()
    {
        while (greater.size() > less.size())
        {
            auto it = greater.begin();
            less.insert(*it);
            less_sum += *it;

            greater_sum -= *it;
            greater.erase(it);
        }
        while (less.size() > greater.size() + 1)
        {
            auto it = less.begin();
            greater.insert(*it);
            greater_sum += *it;

            less_sum -= *it;
            less.erase(less.begin());
        }
    }
};
```

## 可插稀疏表

```c++
class ST {
private:
    int n;
    std::vector<std::array<i64, L>> a;
public:
    ST() {
        n = -1; // 注意一定要初始化成 -1
        insert(0);
    }
    void insert(i64 val) {
        a.push_back(std::array<i64, L>{});
        a[++n][0] = val;
        for (int l = 1; (1 << l) <= n; l++) {
            a[n][l] = std::max(a[n][l - 1], a[n - (1 << l - 1)][l - 1]);
        }
    }

    i64 ask(int l, int r) {
        int len = Log[r - l + 1];
        return std::max(a[l + (1 << len) - 1][len], a[r][len]);
    }
};
```

## 普通左开右闭线段树

```c++
// Luogu P3373
// 区间求和，区间加，区间乘
// 左开右闭线段树，把询问也转换成左开右闭的
// 注意区间加的时候，乘区间长度
int a[N];
i64 tr[N << 2], t1[N << 2], t2[N << 2];

void push_down(int cur, int len) {
    if (t1[cur] == 1 && t2[cur] == 0) {
        return;
    }
    (tr[cur << 1] *= t1[cur]) %= Mod;
    (tr[cur << 1] += 1ll * t2[cur] * (len >> 1) % Mod) %= Mod;
    (t1[cur << 1] *= t1[cur]) %= Mod;
    (t2[cur << 1] *= t1[cur]) %= Mod;
    (t2[cur << 1] += t2[cur]) %= Mod;
    (tr[cur << 1 | 1] *= t1[cur]) %= Mod;
    (tr[cur << 1 | 1] += 1ll * t2[cur] * (len + 1 >> 1) % Mod) %= Mod;
    (t1[cur << 1 | 1] *= t1[cur]) %= Mod;
    (t2[cur << 1 | 1] *= t1[cur]) %= Mod;
    (t2[cur << 1 | 1] += t2[cur]) %= Mod;

    t1[cur] = 1, t2[cur] = 0;
}

void push_up(int cur) {
    tr[cur] = (tr[cur << 1] + tr[cur << 1 | 1]) % Mod;
    return;
}

void build(int cur, int l, int r) {
    tr[cur] = t2[cur] = 0;
    t1[cur] = 1;
    if (l + 1 == r) {
        tr[cur] = a[l];
        return;
    }

    int m = l + r >> 1;
    build(cur << 1, l, m);
    build(cur << 1 | 1, m, r);

    push_up(cur);
}

i64 quiry(int cur, int l, int r, int sl, int sr) {
    if (sl <= l && r <= sr) {
        return tr[cur];
    }

    push_down(cur, r - l);

    int m = l + r >> 1;
    int res = 0;
    if (m > sl) {
        res += quiry(cur << 1, l, m, sl, sr);
    }
    if (m < sr) {
        res += quiry(cur << 1 | 1, m, r, sl, sr);
    }

    return res % Mod;
}

void upd(int cur, int l, int r, int sl, int sr, i64 val, int op) {
    if (sl <= l && r <= sr) {
        if (op == 1) {
            (tr[cur] *= val) %= Mod;
            (t1[cur] *= val) %= Mod;
            (t2[cur] *= val) %= Mod;
        }
        else {
            (tr[cur] += 1ll * val * (r - l) % Mod) %= Mod;
            (t2[cur] += val) %= Mod;
        }
        return;
    }

    push_down(cur, r - l);

    int m = l + r >> 1;
    if (m > sl) {
        upd(cur << 1, l, m, sl, sr, val, op);
    }
    if (m < sr) {
        upd(cur << 1 | 1, m, r, sl, sr, val, op);
    }

    push_up(cur);
}

void solve(){
    int n = 0, q = 0;
    std::cin >> n >> q >> Mod;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    build(1, 0, n);
    while (q--) {
        int op = 0, l = 0, r = 0;
        std::cin >> op >> l >> r;
        l--;
        if (op == 3) {
            std::cout << quiry(1, 0, n, l, r) << '\n';
        }
        else {
            int x = 0;
            std::cin >> x;
            x %= Mod;
            upd(1, 0, n, l, r, x, op);
        }
    }
    return;
}
```

## 可持久化权值线段树

```c++
// Luogu P3919 查询区间第 k 大
struct Node {
    int l, r;
    int sum;
} tr[N << 5];
int cnt;

int New(int old) {
    tr[cnt] = tr[old];
    return cnt++;
}

void push_up(int cur) {
    auto &[l, r, sum] = tr[cur];
    sum = tr[l].sum + tr[r].sum;
}

int build(int l, int r) {
    int cur = cnt++;
    if (l + 1 == r) {
        return cur;
    }
    int m = l + r >> 1;
    tr[cur].l = build(l, m);;
    tr[cur].r = build(m, r);;
    return cur;
}

int upd(int old, int l, int r, int pos) {
    int cur = New(old);
    if (l + 1 == r) {
        tr[cur].sum++;
        return cur;
    }
    int m = l + r >> 1;
    if (m > pos) {
        tr[cur].l = upd(tr[cur].l, l, m, pos);
    }
    else {
        tr[cur].r = upd(tr[cur].r, m, r, pos);
    }

    push_up(cur);
    return cur;
}

int quiry(int lcur, int rcur, int l, int r, int k) {
    if (l + 1 == r) {
        return l;
    }

    int m = l + r >> 1;
    int num = tr[tr[rcur].l].sum - tr[tr[lcur].l].sum;
    if (num >= k) {
        return quiry(tr[lcur].l, tr[rcur].l, l, m, k);
    }
    else {
        return quiry(tr[lcur].r, tr[rcur].r, m, r, k - num);
    }
}

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    h.assign(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        h[i] = a[i];
    }
    std::sort(h.begin(), h.end());
    h.erase(std::unique(h.begin(), h.end()), h.end());
    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(h.begin(), h.end(), a[i]) - h.begin();
    }

    for (int i = 0; i < q; i++) {
        int l = 0, r = 0, k = 0;
        std::cin >> l >> r >> k;
        l--, r--;
        qr[r].push_back({ i, l, k });
    }

    int *const rt = sp + 1;
    rt[-1] = build(0, h.size());
    for (int r = 0; r < n; r++) {
        rt[r] = upd(rt[r - 1], 0, h.size(), a[r]);
        for (auto &[idx, l, k] : qr[r]) {
            ans[idx] = h[quiry(rt[l - 1], rt[r], 0, h.size(), k)];
        }
    }

    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << '\n';
    }
}
```

## 可持久化字典树

```cpp
int a[N + 5];

int rt[N + 5], cnt;
// tr[i][2] AKA siz[i]
std::array<int, 3> tr[N << 5]; // about 32N

int New() {
    tr[cnt] = { 0, 0, 0 }; // init
    return cnt++;
}
void insert(int cur, int old, int x) {
    for (int i = 29; i >= 0; i--) {
        tr[cur][2] = tr[old][2] + 1;
        int b = x >> i & 1;
        tr[cur][b] = New(); // likewise, persistent segment-tree, create new node to insert or modify
        tr[cur][b ^ 1] = tr[old][b ^ 1];
        old = tr[old][b];
        cur = tr[cur][b];
    }
    tr[cur][2] = tr[old][2] + 1;
}
int ask(int l, int r, int x) {
    int ans = 0;
    for (int i = 29; ~i; i--) {
        int b = x >> i & 1;
        if (tr[tr[r][b ^ 1]][2] - tr[tr[l][b ^ 1]][2] > 0) {
            b ^= 1;
            ans |= (1 << i);
        }
        l = tr[l][b], r = tr[r][b];
    }
    return ans;
}

void solve()
{
    cnt = 1; // started from 1
    rt[0] = New();
    int n = 0, q = 0;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        rt[i] = New();
        insert(rt[i], rt[i - 1], a[i]);
    }
    for (int i = 0; i < q; i++) {
        int l = 0, r = 0, x = 0;
        std::cin >> l >> r >> x;
        std::cout << ask(rt[l - 1], rt[r], x) << '\n';
    }

    return;
}
```
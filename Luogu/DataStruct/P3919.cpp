#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e6, Q = 1e6, Inf = 2e9;

struct Node {
    int l, r;
    int val;
} tr[N << 5];
int cnt = 0;

int a[N], rt[Q + 5];

// 新建一个与 tr[cur] 一样的节点并返回该节点的编号
int New(int cur) {
    tr[cnt] = tr[cur];
    return cnt++;
}

int build(int l, int r) {
    int cur = cnt++;
    if (l + 1 == r) {
        tr[cur].val = a[l];
        return cur;
    }

    int m = l + r >> 1;
    tr[cur].l = build(l, m);
    tr[cur].r = build(m, r);

    return cur;
}

int upd(int cur, int l, int r, int pos, int val) {
    int now = New(cur);
    if (l + 1 == r) {
        tr[now].val = val;
        return now;
    }

    int m = l + r >> 1;
    if (m > pos) {
        tr[now].l = upd(tr[now].l, l, m, pos, val);
    }
    else {
        tr[now].r = upd(tr[now].r, m, r, pos, val);
    }
    return now;
}

int quiry(int cur, int l, int r, int pos) {
    if (l + 1 == r) {
        return tr[cur].val;
    }

    int m = l + r >> 1;
    if (m > pos) {
        return quiry(tr[cur].l, l, m, pos);
    }
    else {
        return quiry(tr[cur].r, m, r, pos);
    }
}

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    rt[0] = build(0, n);
    for (int i = 1; i <= q; i++) {
        int ver = 0, op = 0, idx = 0;
        std::cin >> ver >> op >> idx;
        idx--;
        if (op == 1) {
            int val = 0;
            std::cin >> val;
            rt[i] = upd(rt[ver], 0, n, idx, val);
        }
        else {
            std::cout << quiry(rt[ver], 0, n, idx) << '\n';
            rt[i] = rt[ver];
        }

    }
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
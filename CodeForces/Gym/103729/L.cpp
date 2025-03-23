#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

struct Node {
    i64 sum;
    int cnt;

    Node operator+ (const Node& a) const {
        Node res;
        res.sum = sum + a.sum;
        res.cnt = cnt + a.cnt;
        return res;
    }
} tr[N << 2];
i64 tag[N << 2];

void push_down(int cur) {
    int l = cur << 1, r = cur << 1 | 1;
    tr[l].sum += tag[cur] * tr[l].cnt;
    tr[r].sum += tag[cur] * tr[r].cnt;
    tag[l] += tag[cur];
    tag[r] += tag[cur];
    tag[cur] = 0;
}

int a[N + 5], s[N + 5];

void build(int cur, int l, int r) {
    if (l == r) {
        tr[cur].sum = a[l];
        tr[cur].cnt = (s[l] == 1);
        return;
    }
    
    int m = l + r >> 1;
    build(cur << 1, l, m);
    build(cur << 1 | 1, m + 1, r);

    tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
    return;
}

void upd(int cur, int l, int r, int pos, int val) {
    if (l == r) {
        tr[cur].cnt += val;
        return;
    }

    push_down(cur);

    int m = l + r >> 1;
    if (pos <= m) {
        upd(cur << 1, l, m, pos, val);
    }
    else {
        upd(cur << 1 | 1, m + 1, r, pos, val);
    }

    tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
    return;
}

void upd(int cur, int l, int r, int sl, int sr, int val) {
    if (sl <= l && r <= sr) {
        tag[cur] += val;
        tr[cur].sum += 1ll * val * tr[cur].cnt;
        return;
    }

    push_down(cur);

    int m = l + r >> 1;
    if (m >= sl) {
        upd(cur << 1, l, m, sl, sr, val);
    }
    if (m < sr) {
        upd(cur << 1 | 1, m + 1, r, sl, sr, val);
    }

    tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
    return;
}

i64 quiry(int cur, int l, int r, int sl, int sr) {
    if (sl <= l && r <= sr) {
        return tr[cur].sum;
    }

    push_down(cur);

    int m = l + r >> 1;
    i64 res = 0;
    if (m >= sl) {
        res += quiry(cur << 1, l, m, sl, sr);
    }
    if (m < sr) {
        res += quiry(cur << 1 | 1, m + 1, r, sl, sr);
    }

    tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];

    return res;
}

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
    }

    build(1, 1, n);
    while (q--) {
        int op = 0;
        std::cin >> op;
        if (op == 1) {
            int x = 0;
            std::cin >> x;
            upd(1, 1, n, x, -1);
        }
        else if (op == 2) {
            int x = 0;
            std::cin >> x;
            upd(1, 1, n, x, 1);
        }
        else {
            int l = 0, r = 0;
            std::cin >> l >> r;
            if (op == 3) {
                int x = 0;
                std::cin >> x;
                upd(1, 1, n, l, r, x);
            }
            else {
                std::cout << quiry(1, 1, n, l, r) << '\n';
            }
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

    return 0;
}
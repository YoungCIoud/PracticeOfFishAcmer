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

constexpr int N = 1e5, Inf = 1e9;
int Mod;

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
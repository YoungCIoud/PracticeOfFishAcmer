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
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7, Inf = 1e18;
constexpr int N = 1e6;

int a[N + 5];
i64 tr[N << 2], t1[N << 2], t2[N << 2];
bool used[N << 2];

void push_down(int cur) {
    int l = cur << 1, r = cur << 1 | 1;
    if (used[cur]) {
        tr[l] = tr[r] = t1[cur] + t2[cur];
        t1[l] = t1[r] = t1[cur];
        t2[l] = t2[r] = t2[cur];
        used[l] = used[r] = true;
    }
    else if (t2[cur] != 0) {
        tr[l] += t2[cur], tr[r] += t2[cur];
        t2[l] += t2[cur], t2[r] += t2[cur];
    }
    t1[cur] = t2[cur] = 0;
    used[cur] = false;
} 
void push_up(int cur) {
    tr[cur] = std::max(tr[cur << 1], tr[cur << 1 | 1]);
}
void build(int cur, int l, int r) {
    tr[cur] = -Inf;
    if (l == r) {
        tr[cur] = a[l];
        t1[cur] = a[l];
        t2[cur] = 0ll;
        used[cur] = true;
        return;
    }
    int m = l + r >> 1;
    build (cur << 1, l, m);
    build (cur << 1 | 1, m + 1, r);
    push_up(cur);
}
void upd(int cur, int l, int r, int sl, int sr, i64 val) {
    if (sl <= l && r <= sr) {
        tr[cur] = val;
        t1[cur] = val;
        used[cur] = true;
        t2[cur] = 0;
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

    push_up(cur);
}
void add(int cur, int l, int r, int sl, int sr, i64 val) {
    if (sl <= l && r <= sr) {
        tr[cur] += val;
        t2[cur] += val;
        return;
    }

    push_down(cur);

    int m = l + r >> 1;
    if (m >= sl) {
        add(cur << 1, l, m, sl, sr, val);
    }
    if (m < sr) {
        add(cur << 1 | 1, m + 1, r, sl, sr, val);
    }

    push_up(cur);
}
i64 quiry(int cur, int l, int r, int sl, int sr) {
    if (sl <= l && r <= sr) {
        return tr[cur];
    }

    push_down(cur);

    int m = l + r >> 1;
    i64 L = -Inf, R = -Inf;
    if (m >= sl) {
        L = quiry (cur << 1, l, m, sl,  sr);
    }
    if (m < sr) {
        R = quiry (cur << 1 | 1, m + 1, r, sl, sr);
    }

    return std::max(L, R);
}

void solve() {
    int n = 0, q = 0;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    build(1, 1, n);

    while (q--) {
        int op = 0, l = 0, r = 0;
        std::cin >> op >> l >> r;
        if (op == 1) {
            int x = 0;
            std::cin >> x;
            upd(1, 1, n, l, r, x);
        }
        else if (op == 2) {
            int x = 0;
            std::cin >> x;
            add(1, 1, n, l, r, x);
        }
        else {
            std::cout << quiry(1, 1, n, l, r) << '\n';
        }
    }
    return;
}

int main () {
    IOS;
    int _t = 1;
   // std::cin >> _t;

    while (_t--) {
        solve();
    }

    return 0;
}
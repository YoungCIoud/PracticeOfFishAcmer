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
constexpr int N = 5e5, M = 1e5, Inf = 1e9;

int a[N + 5 << 1], h[N + 5 << 1], top;

int qr[N + 5], ans[N + 5];

std::multiset<int> ms;

// 左闭右开权值线段树
struct Node {
    int l, r;
    int mn;
} tr[N << 3];

void build(int cur, int l, int r) {
    tr[cur].l = Inf, tr[cur].r = -1;
    tr[cur].mn = Inf;
    if (l + 1 == r) {
        return;
    }

    int m = l + r >> 1;
    build(cur << 1, l, m);
    build(cur << 1 | 1, m, r);
}

void add(int cur, int l, int r, int pos) {
    if (l + 1 == r) {
        if (tr[cur].l == Inf) {
            tr[cur].l = tr[cur].r = pos;
        }
        else {
            tr[cur].mn = 0;
        }
        return;
    }

    int m = l + r >> 1;
    if (m > pos) {
        add(cur << 1, l, m, pos);
    }
    else {
        add(cur << 1 | 1, m, r, pos);
    }

    // push_up
    tr[cur].l = std::min(tr[cur << 1].l, tr[cur << 1 | 1].l);
    tr[cur].r = std::max(tr[cur << 1].r, tr[cur << 1 | 1].r);
    tr[cur].mn = std::min({ tr[cur].mn, tr[cur << 1].mn, tr[cur << 1 | 1].mn });
    if (~tr[cur << 1].r && ~tr[cur << 1 | 1].r) {
        tr[cur].mn = std::min(tr[cur].mn, std::abs(h[tr[cur << 1].r] - h[tr[cur << 1 | 1].l]));
    }

    return;
}

void solve() {
    int n = 0, q = 0;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        if (i > 1) {
            ms.insert(std::abs(a[i] - a[i - 1]));
        }
        a[i + n] = a[i];
        h[top++] = a[i];
    }

    for (int i = 0; i < q; i++) {
        ans[i] = -1, qr[i] = -1;
        std::string s;
        std::cin >> s;
        if (s.size() == 6) {
            int idx = 0, val = 0;
            std::cin >> idx >> val;
            qr[i] = val;
            h[top++] = val;

            // Solve MIN_GAP
            if (idx < n) {
                ms.erase(ms.find(std::abs(a[idx + n] - a[idx + 1])));
                ms.insert(std::abs(val - a[idx + 1]));
            }
            ms.insert(std::abs(a[idx + n] - val));
            a[idx + n] = val;
        }
        else if (s.size() == 7) {
            ans[i] = *(ms.begin());
        }
    }
    
    std::sort(h, h + top);
    // unique
    int tmp = 1;
    for (int i = 1; i < top; i++) {
        if (h[i] != h[i - 1]) {
            h[tmp++] = h[i];
        }
    }
    top = tmp;

    build(1, 0, top);

    for (int i = 1; i <= n; i++) {
        add(1, 0, top, std::lower_bound(h, h + top, a[i]) - h);
    }
    for (int i = 0; i < q; i++) {
        if (~qr[i]) {
            add(1, 0, top, std::lower_bound(h, h + top, qr[i]) - h);
        }
        else if (ans[i] == -1) {
            ans[i] = tr[1].mn;
        }
    }

    for (int i = 0; i < q; i++) {
        if (~ans[i]) {
            std::cout << ans[i] << '\n';
        }
    }
    return;
}

int main() {
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
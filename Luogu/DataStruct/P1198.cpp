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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 2e5, Inf = 2e9;

int tr[N << 2];
void build(int cur, int l, int r) {
    if (l == r) {
        tr[cur] = -Inf;
        return;
    }
    int m = l + r >> 1;
    build (cur << 1, l, m);
    build (cur << 1 | 1, m + 1, r);
}
void add(int cur, int l, int r, int pos, int val) {
    if (l == r) {
        tr[cur] = val;
        return;
    }
    int m = l + r >> 1;
    if (m >= pos) {
        add (cur << 1, l, m, pos, val);
    }
    else {
        add (cur << 1 | 1, m + 1, r, pos, val);
    }

    tr[cur] = std::max(tr[cur << 1], tr[cur << 1 | 1]);
}
int quiry(int cur, int l, int r, int sl, int sr) {
    if (sl <= l && r <= sr) {
        return tr[cur];
    }
    int m = l + r >> 1;
    int L = -Inf, R = -Inf;
    if (m >= sl) {
        L = quiry (cur << 1, l, m, sl,  sr);
    }
    if (m < sr) {
        R = quiry (cur << 1 | 1, m + 1, r, sl, sr);
    }
    return std::max(L, R);
}

void solve() {
    int q = 0, p = 0;
    std::cin >> q >> p;

    int t = 0;
    int n = 0;
    build(1, 1, N);
    while (q--) {
        char op{};
        std::cin >> op;
        if (op == 'Q') {
            int L = 0;
            std::cin >> L;
            t = quiry(1, 1, N, n - L + 1, N);
            std::cout << t << '\n';
        }
        else {
            i64 x;
            std::cin >> x;
            n++;
            add(1, 1, N, n, (t + x) % p);
        }
    }
    
    return;
}

int main () {
    int _t = 1;
   // std::cin >> _t;

    while (_t--) {
        solve();
    }

    return 0;
}
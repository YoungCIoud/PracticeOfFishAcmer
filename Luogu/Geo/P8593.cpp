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
constexpr int N = 5e5;
constexpr double G = 9.8, Inf = 1e18;

struct MISSILE {
    int id;
    int y, x0;
    double xt;
    bool operator<(const MISSILE &a) const {
        return (y == a.y ? x0 < a.x0 : y < a.y);
    }
} ms[N + 5];

int a[N + 5];

int tot;
double h[N + 5];
int tr[N + 5];

void init() {
    for (int i = 1; i <= tot; i++) {
        tr[i] = 0;
    }
}

int lowbit(int x) {
    return x & -x;
}

void add(int pos) {
    while (pos <= tot) {
        tr[pos]++;
        pos += lowbit(pos);
    }
    return;
}

int ask(int pos) {
    int res = 0;
    while (pos > 0) {
        res += tr[pos];
        pos -= lowbit(pos);
    }
    return res;
}

void cnt(int l, int r) {
    tot = 0;
    h[tot++] = -Inf;
    for (int i = l; i < r; i++) {
        h[tot++] = ms[i].xt;
    }
    std::sort(h, h + tot);
    int tmp = tot;
    tot = 1;
    for (int i = 1; i < tmp; i++) {
        if (h[i] != h[i - 1]) {
            h[tot++] = h[i];
        }
    }
    tot--;
    
    init();
    for (int i = l; i < r; i++) {
        int hv = std::lower_bound(h, h + tot + 1, ms[i].xt) - h;
        a[ms[i].id] += ask(tot) - ask(hv - 1);
        add(hv);
    }
    init();
    for (int i = r - 1; i >= l; i--) {
        int hv = std::lower_bound(h, h + tot + 1, ms[i].xt) - h;
        a[ms[i].id] += ask(hv);
        add(hv);
    }
    return;
}


void solve() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x = 0, y = 0, v = 0;
        std::cin >> x >> y >> v;
        double xt = x + 1.0 * v * std::sqrt(2.0 * y / G);
        ms[i] = { i, y, x, xt };
    }
    std::sort(ms, ms + n);

    for (int l = 0, r = 1; l < n; l = r) {
        while (r < n && ms[r].y == ms[l].y) {
            r++;
        }
        cnt(l, r);
    }
    
    i64 sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        int dc = 0;
        std::cin >> dc;
        a[i] = std::min(a[i], dc);
    }
    
    std::sort(a, a + n, 
            [](int &u, int &v) { return u > v; });

    for (int i = 0; i < m; i++) {
        sum -= a[i];
    }
    std::cout << sum << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
//    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
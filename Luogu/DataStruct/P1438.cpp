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
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

i64 K[N << 2], D[N << 2];
i64 a[N + 5];

void add(int cur, int l, int r, int sl, int sr, i64 k, int d) {
    if (sl <= l && r <= sr) {
        K[cur] += k + d * (l - sl);
        D[cur] += d;

        if (l == r) {
            a[l] += K[cur];
            K[cur] = D[cur] = 0;
        }

        return;
    }
    
    int m = l + r >> 1;

    if (K[cur] || D[cur]) {
        K[cur << 1] += K[cur];
        D[cur << 1] += D[cur];

        K[cur << 1 | 1] += K[cur] + D[cur] * (m + 1 - l);
        D[cur << 1 | 1] += D[cur];

        D[cur] = K[cur] = 0;
    }

    if (m >= sl) {
        add(cur << 1, l, m, sl, sr, k, d);
    }
    if (m < sr) {
        add(cur << 1 | 1, m + 1, r, sl, sr, k, d);
    }
    return;
}

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    while (q--) {
        int op = 0;
        std::cin >> op;
        if (op == 1) {
            int l, r, k, d;
            std::cin >> l >> r >> k >> d;
            add(1, 1, n, l, r, k, d);
        }
        else {
            int pos = 0;
            std::cin >> pos;
            add(1, 1, n, pos, pos, 0, 0);
            std::cout << a[pos] << '\n';
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
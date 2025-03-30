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
constexpr int N = 1e5, Q = 1e5, Inf = 1e9;

int a[N];

std::array<int, 3> tr[N << 2];
int tag[N << 2];
i64 fac[N + 5], invfac[N + 5];

i64 qpow(i64 a, i64 p) {
    i64 res = 1;
    while (p) {
        if (p & 1) {
            (res *= a) %= Mod;
        }
        (a *= a) %= Mod;
        p >>= 1;
    }
    return res;
}
i64 inv(i64 a) {
    return qpow(a, Mod - 2);
}
i64 C(int n, int m) {
    return fac[n] * invfac[m] % Mod * invfac[n - m] % Mod;
}

std::array<int, 3> operator+(const std::array<int, 3>& l, const std::array<int, 3>& r) {
    return { l[0], l[1] + r[1] + (l[2] >= r[0]), r[2] };
}

void push_up(int cur) {
    tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
}

void move(int cur, int c) {
    (tag[cur] += c) %= 4;
    (tr[cur][0] += c) %= 4;
    (tr[cur][2] += c) %= 4;
    tr[cur][1] += (tr[cur][2] < c) - (tr[cur][0] < c);
}

void push_down(int cur) {
    move(cur << 1, tag[cur]);
    move(cur << 1 | 1, tag[cur]);
    tag[cur] = 0;
    return;
}

void build(int cur, int l, int r) {
    if (l + 1 == r) {
        tr[cur][0] = tr[cur][2] = a[l];
        tr[cur][1] = 0;
        return;
    }

    int m = l + r >> 1;
    build(cur << 1, l, m);
    build(cur << 1 | 1, m, r);
    push_up(cur);
}
void upd(int cur, int l, int r, int sl, int sr) {
    if (sl <= l && r <= sr) {
        move(cur, 1);
        return;
    }

    if (tag[cur]) {
        push_down(cur);
    }
    int m = l + r >> 1;
    if (m > sl) {
        upd(cur << 1, l, m, sl, sr);
    }
    if (m < sr) {
        upd(cur << 1 | 1, m, r, sl, sr);
    }
    push_up(cur);
}

std::array<int, 3> quiry(int cur, int l, int r, int sl, int sr) {
    if (sl <= l && r <= sr) {
        return tr[cur];
    }

    if (tag[cur]) {
        push_down(cur);
    }
    int m = l + r >> 1;
    if (m >= sr) {
        return quiry(cur << 1, l, m, sl, sr);
    }
    else if (m <= sl) {
        return quiry(cur << 1 | 1, m, r, sl, sr);
    }
    else {
        return quiry(cur << 1, l, m, sl, sr) + quiry(cur << 1 | 1, m, r, sl, sr);
    }
}

void solve()
{
    int n = 0, q = 0;
    std::string s;
    std::cin >> n >> q >> s;
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - 'A';
    }

    build (1, 0, n);
    while (q--) {
        int op = 0;
        int l = 0, r = 0;
        std::cin >> op >> l >> r;
        l--;
        if (op == 1) {
            upd(1, 0, n, l, r);
        }
        else {
            int k = 0;
            std::cin >> k;
            int c = quiry(1, 0, n, l, r)[1];

            if (k <= c || k > r - l) {
                std::cout << 0 << '\n';
            }
            else {
                std::cout << C(r - l - 1 - c, k - 1 - c) << '\n';
            }
        }
    }
}

int main()
{
    IOS;
    int _t = 1;
    
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = 1ll * i * fac[i -  1] % Mod;
    }
    invfac[N] = inv(fac[N]);
    for (int i = N; i >= 1; i--) {
        invfac[i - 1] = 1ll * i * invfac[i] % Mod;
    }

    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}

/*
5 6
BACDA
2 1 4 2
1 2 3
2 1 5 4
1 2 3
2 1 5 4
2 1 5 5
*/
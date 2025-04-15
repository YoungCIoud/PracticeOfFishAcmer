#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), \
                std::cin.tie(0), \
                std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, Q = 1e5, L = 30;

std::vector<int> g[N + 5];

int siz[N + 5];
int pos[N + 5], tim;
void dfs(int cur, int fa) {
    siz[cur] = 1;
    pos[cur] = tim++;
    
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        dfs(to, cur);
        siz[cur] += siz[to];
    }
}

void insert(std::array<int, L> &base, int val) {
    for (int i = L - 1; ~i; i--) {
        if (!(val >> i & 1)) {
            continue;
        }

        if (base[i]) {
            val ^= base[i];
        }
        else {
            for (int j = j - 1; ~j; j--) {
                if (val >> j & 1) {
                    val ^= base[j];
                }
            }
            for (int j = i + 1; j < L; j++) {
                if (base[j] >> i & 1) {
                        base[j] ^= val;
                }
            }
            base[i] = val;
            return;
        }
    }
}

std::array<int, L> operator+ (std::array<int, L> u, const std::array<int, L> &v) {
    for (int i = 0; i < L; i++) {
        if (v[i]) {
            insert(u, v[i]);
        }
    }
    return u;
}

std::array<int, L> tr[N << 2];
void build(int cur, int l, int r) {
    for (int i = 0; i < L; i++) {
        tr[cur][i] = 0;
    }
    if (l + 1 == r) {
        return;
    }

    int m = l + r >> 1;
    build(cur << 1, l, m);
    build(cur << 1 | 1, m, r);
}

void upd(int cur, int l, int r, int pos, int val) {
    insert(tr[cur], val);
    if (l + 1 == r) {
        return;
    }

    int m = r + l >> 1;
    if (pos < m) {
        upd(cur << 1, l, m, pos, val);
    }
    else {
        upd(cur << 1 | 1, m, r, pos, val);
    }
}

std::array<int, L> quiry(int cur, int l, int r, int sl, int sr) {
    if (sl <= l && r <= sr) {
        return tr[cur];
    }

    int m = r + l >> 1;
    if (sr <= m) {
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
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        siz[i] = 0;
        tim = 0;
    }
    
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);
    build(1, 0, n);
    while (q--) {
        int op = 0, x = 0, y = 0;
        std::cin >> op >> x >> y;
        if (op == 1) {
            upd(1, 0, n, pos[x], y);
        }
        else {
            std::vector<int> base;
            for (auto &p : quiry(1, 0, n, pos[x], pos[x] + siz[x])) {
                if (p) {
                    base.push_back(p);
                }
            }
            int ans = 0;
            if (y >= (1 << base.size())) {
                ans = -1;
            }
            else {
                int i = 0;
                while (y) {
                    if (y & 1) {
                        ans ^= base[i];
                    }
                    i++;
                    y >>= 1;
                }
            }
            std::cout << ans << '\n';
        }
    }
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
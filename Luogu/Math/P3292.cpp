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
constexpr int N = 2e4, Q = 2e5, L = 63, B = 20;

class LinerBase {
private:
    i64 p[64];
public:
    LinerBase() {
        for (int i = 0; i < L; i++) {
            p[i] = 0;
        }
    }
    i64& operator[](int idx) {
        return p[idx];
    }

    void insert (i64 x) {
        for (int i = L - 1; i >= 0 && x; i--) {
            if (!(x >> i & 1)) {
                continue;
            }
        
            if (p[i]) {
                x ^= p[i];
            }
            else {
                for (int j = i - 1; j >= 0; j--) {
                    if (x >> j & 1) {
                        x ^= p[j];
                    }
                }
                p[i] = x;
                for (int j = i + 1; j < L; j++) {
                    if (p[j] >> i & 1) {
                        p[j] ^= x;
                    }
                }
                return;
            }
        }
    }

    void merge(LinerBase v) {
        for (int i = 0; i < L; i++) {
            insert(v[i]);
        }
    }
};

i64 a[N + 5];
std::vector<int> g[N + 5];
int deep[N + 5];

int st_f[N + 5][B];
LinerBase st_l[N + 5][B];

void dfs(int cur, int fa, int d) {
    deep[cur] = d;
    st_f[cur][0] = fa;
    st_l[cur][0].insert(a[cur]);

    for (auto &to : g[cur]) {
        if (to != fa) {
            dfs(to, cur, d + 1);
        }
    }
}

int lca(int x, int y) {
    if (deep[x] != deep[y]) {
        for (int l = B - 1; ~l; l--) {
            int to = st_f[y][l];
            if (deep[to] >= deep[x]) {
                y = to;
            }
        }
    }

    if (x == y) {
        return x;
    }

    for (int l = B - 1; ~l; l--) {
        int xx = st_f[x][l];
        int yy = st_f[y][l];
        if (xx != yy) {
            x = xx;
            y = yy;
        }
    }
    return st_f[x][0];
}

LinerBase ask(int x, int y) {
    LinerBase res;
    for (int l = B - 1; ~l; l--) {
        int to = st_f[y][l];
        if (deep[to] >= deep[x]) {
            res.merge(st_l[y][l]);
            y = to;
        }
    }
    return res;
}

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0, 1);
    for (int l = 1; l < B; l++) {
        for (int i = 1; i <= n; i++) {
            if (deep[i] < (1 << l)) {
                continue;
            }

            int fa = st_f[i][l - 1];
            st_f[i][l] = st_f[fa][l - 1];
            st_l[i][l] = st_l[i][l - 1];
            st_l[i][l].merge(st_l[fa][l - 1]);
        }
    }

    while (q--) {
        int x = 0, y = 0;
        std::cin >> x >> y; 
        if (deep[x] > deep[y]) {
            std::swap(x, y);
        }

        int fa = lca(x, y);
        // std::cout << fa << '\n';
        
        LinerBase base = ask(fa, y);
        if (fa != x) {
            base.merge(ask(fa, x));
        }
        base.insert(a[fa]);

        i64 ans = 0;
        for (int i = 0; i < L; i++) {
            ans ^= base[i];
        }
        std::cout << ans << '\n';
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
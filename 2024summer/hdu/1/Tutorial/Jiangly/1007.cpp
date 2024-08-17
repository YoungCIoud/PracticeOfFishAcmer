#include <bits/stdc++.h>

using i64 = long long;
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n_ = 0) {
        init(n_);
    }
    
    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }
    
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> f(n), g(n);
    for (int i = 0; i < n; i++) {
        std::cin >> f[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> g[i];
    }
    
    std::vector<int> pf(n), pg(n);
    std::iota(pf.begin(), pf.end(), 0);
    std::sort(pf.begin(), pf.end(),
        [&](int i, int j) {
            if (f[i] != f[j]) {
                return f[i] < f[j];
            }
            return i > j;
        });
    std::iota(pg.begin(), pg.end(), 0);
    std::sort(pg.begin(), pg.end(),
        [&](int i, int j) {
            if (g[i] != g[j]) {
                return g[i] < g[j];
            }
            return i > j;
        });
    for (int i = 0; i < n; i++) {
        f[pf[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        g[pg[i]] = i;
    }
    
    std::vector<int> deg(n);
    std::iota(deg.begin(), deg.end(), 0);
    
    i64 ans = 1LL * n * (n - 1) * (n - 2) / 6;
    
    Fenwick<int> fen(n);
    auto solve = [&](auto self, int l, int r) -> void {
        if (r - l == 1) {
            return;
        }
        int m = (l + r) / 2;
        assert(std::stable_partition(pf.begin() + l, pf.begin() + r,
            [&](int x) {
                return x < m;
            }) == pf.begin() + m);
        int j = r;
        for (int i = m - 1; i >= l; i--) {
            while (j > m && f[pf[j - 1]] > f[pf[i]]) {
                j--;
                fen.add(g[pf[j]], 1);
            }
            deg[pf[i]] += fen.rangeSum(g[pf[i]], n);
        }
        while (j < r) {
            fen.add(g[pf[j]], -1);
            j++;
        }
        j = l;
        for (int i = m; i < r; i++) {
            while (j < m && f[pf[j]] < f[pf[i]]) {
                fen.add(g[pf[j]], 1);
                j++;
            }
            deg[pf[i]] -= fen.sum(g[pf[i]]);
        }
        while (j > l) {
            j--;
            fen.add(g[pf[j]], -1);
        }
        self(self, l, m);
        self(self, m, r);
    };
    solve(solve, 0, n);
    
    for (int i = 0; i < n; i++) {
        ans -= 1LL * deg[i] * (deg[i] - 1) / 2;
    }
    std::cout << ans << "\n";
    
    return 0;
}

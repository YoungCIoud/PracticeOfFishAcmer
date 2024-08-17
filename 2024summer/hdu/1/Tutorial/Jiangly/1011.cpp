#include <bits/stdc++.h>

using i64 = long long;
struct HLD {
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    int cur;
    
    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 0) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    
    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        
        int d = dep[u] - k;
        
        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }
        
        return seq[in[u] - dep[u] + d];
    }
    
    bool isAncester(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    
    int rootedParent(int u, int v) {
        std::swap(u, v);
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return parent[u];
        }
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    
    int rootedSize(int u, int v) {
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }
    
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};
template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    LazySegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F &&pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

constexpr int inf = 1E9;
struct Tag {
    int add = 0;
    void apply(const Tag &t) & {
        add += t.add;
    }
};
struct Info {
    int min = inf;
    int cnt = 0;
    void apply(const Tag &t) & {
        min += t.add;
    }
};
Info operator+(const Info &a, const Info &b) {
    if (a.min < b.min) {
        return a;
    }
    if (a.min > b.min) {
        return b;
    }
    return Info {a.min, a.cnt + b.cnt};
}

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    HLD t(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        x--;
        y--;
        t.addEdge(x, y);
    }
    t.work();
    
    std::vector<std::vector<int>> vec(n + 1);
    for (int i = 0; i < n; i++) {
        vec[a[i]].push_back(i);
    }
    
    for (int x = 0; x <= n; x++) {
        if (vec[x].size() <= 1) {
            continue;
        }
        auto it = std::max_element(vec[x].begin(), vec[x].end(),
            [&](int a, int b) {
                return t.dep[a] < t.dep[b];
            });
        std::swap(vec[x][0], *it);
        int e = vec[x][0];
        std::sort(vec[x].begin() + 1, vec[x].end(),
            [&](int a, int b) {
                bool upa = t.isAncester(a, e);
                bool upb = t.isAncester(b, e);
                if (upa != upb) {
                    return upa;
                }
                if (upa) {
                    return t.dep[a] > t.dep[b];
                } else {
                    return t.dep[a] < t.dep[b];
                }
            });
        // std::cerr << "x : " << x << "\n";
        // for (auto v : vec[x]) {
        //     std::cerr << v + 1 << " ";
        // }
        // std::cerr << "\n";
    }
    
    std::vector<std::array<int, 4>> e;
    auto get = [&](int m) -> i64 {
        LazySegmentTree<Info, Tag> seg {std::vector(n, Info {0, 1})};
        e.clear();
        auto add = [&](int l, int r, int d, int u) {
            if (l == r || d == u) {
                return;
            }
            e.push_back({l, d, u, 1});
            e.push_back({r, d, u, -1});
        };
        auto addSelf = [&](auto arr) {
            const int n = arr.size();
            for (int i = 0; i < n; i++) {
                auto [l1, r1] = arr[i];
                for (int j = 0; j < n; j++) {
                    auto [l2, r2] = arr[j];
                    add(l1, r1, l2, r2);
                }
            }
        };
        auto addEnd = [&](int a, int b) {
            for (auto y : t.adj[a]) {
                if (!t.isAncester(y, b)) {
                    addSelf(std::array{std::make_pair(t.in[y], t.out[y])});
                }
            }
            if (t.isAncester(a, b)) {
                addSelf(std::array{std::make_pair(0, t.in[a]), std::make_pair(t.out[a], n)});
            }
        };
        auto addEnd2 = [&](int b, int a, int c) {
            for (auto y : t.adj[a]) {
                if (!t.isAncester(y, b) && !t.isAncester(y, c)) {
                    addSelf(std::array{std::make_pair(t.in[y], t.out[y])});
                }
            }
            if (t.isAncester(a, b) && t.isAncester(a, c)) {
                addSelf(std::array{std::make_pair(0, t.in[a]), std::make_pair(t.out[a], n)});
            }
        };
        auto addMid = [&](int a, int b) {
            if (t.isAncester(b, a)) {
                std::swap(a, b);
            }
            if (t.isAncester(a, b)) {
                int y = t.rootedParent(b, a);
                addSelf(std::array{std::make_pair(t.in[y], t.in[b]), std::make_pair(t.out[b], t.out[y])});
            } else {
                if (t.in[a] > t.in[b]) {
                    std::swap(a, b);
                }
                addSelf(std::array{std::make_pair(0, t.in[a]), std::make_pair(t.out[a], t.in[b]), std::make_pair(t.out[b], n)});
            }
        };
        for (int i = 0; i < m; i++) {
            if (vec[i].empty()) {
                return 0;
            }
            if (vec[i].size() == 1) {
                int x = vec[i][0];
                for (auto y : t.adj[x]) {
                    addSelf(std::array{std::make_pair(t.in[y], t.out[y])});
                }
                addSelf(std::array{std::make_pair(0, t.in[x]), std::make_pair(t.out[x], n)});
            } else {
                addEnd(vec[i][0], vec[i][1]);
                addEnd(vec[i].back(), vec[i][vec[i].size() - 2]);
                for (int j = 1; j < vec[i].size(); j++) {
                    addMid(vec[i][j - 1], vec[i][j]);
                }
                for (int j = 1; j < vec[i].size() - 1; j++) {
                    addEnd2(vec[i][j - 1], vec[i][j], vec[i][j + 1]);
                }
            }
        }
        std::sort(e.begin(), e.end());
        i64 ans = 0;
        for (int x = 0, i = 0; x < n; x++) {
            while (i < e.size() && e[i][0] <= x) {
                auto [_, l, r, t] = e[i++];
                seg.rangeApply(l, r, Tag {t});
            }
            auto res = seg.rangeQuery(0, n);
            if (res.min == 0) {
                ans += res.cnt;
            }
        }
        return ans;
    };
    
    int lo = 0, hi = n;
    while (lo < hi) {
        int x = (lo + hi + 1) / 2;
        if (get(x) > 0) {
            lo = x;
        } else {
            hi = x - 1;
        }
    }
    std::cout << lo << " " << get(lo) << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

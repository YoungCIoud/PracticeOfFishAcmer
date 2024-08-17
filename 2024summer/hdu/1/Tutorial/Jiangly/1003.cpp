#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

constexpr int M = 1 << 20;

struct Node {
    Node *l = nullptr;
    Node *r = nullptr;
    u64 sum = 0;
    u64 cnt = 0;
} pool[21 << 19];

int tot = 0;
void add(Node *&t, int l, int r, int x) {
    if (t == nullptr) {
        t = &pool[tot++];
    }
    t->sum += u64(x) * x;
    t->cnt += 1;
    if (r - l == 1) {
        return;
    }
    int m = (l + r) / 2;
    if (x < m) {
        add(t->l, l, m, x);
    } else {
        add(t->r, m, r, x);
    }
}

Node *merge(Node *a, Node *b, int l, int r, u64 &ans) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    if (r - l == 1) {
        ans += 2 * a->cnt * b->sum;
        a->sum += b->sum;
        a->cnt += b->cnt;
        return a;
    }
    a->sum += b->sum;
    a->cnt += b->cnt;
    int m = (l + r) / 2;
    if (a->l != nullptr && b->r != nullptr) {
        ans += 2 * a->l->cnt * b->r->sum;
    }
    if (b->l != nullptr && a->r != nullptr) {
        ans += 2 * b->l->cnt * a->r->sum;
    }
    a->l = merge(a->l, b->l, l, m, ans);
    a->r = merge(a->r, b->r, m, r, ans);
    return a;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    std::vector<u64> A(n), S(n), ans(n);
    std::vector<Node *> t(n);
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    
    u64 out = 0;
    auto dfs = [&](auto self, int x, int p) -> void {
        S[x] = A[x];
        ans[x] = A[x] * A[x];
        add(t[x], 0, M, A[x]);
        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            self(self, y, x);
            S[x] += S[y];
            ans[x] += ans[y];
            t[x] = merge(t[x], t[y], 0, M, ans[x]);
        }
        out ^= ans[x] - S[x] * S[x];
    };
    dfs(dfs, 0, -1);
    
    std::cout << out << "\n";
    
    return 0;
}

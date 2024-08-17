#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    int N = 1;
    while (N < 2 * n) {
        N *= 2;
    }
    std::vector<std::vector<std::pair<int, int>>> edges(N);
    
    int tot = n;
    auto work = [&](auto self, int p, int l, int r, int x, int y, int a, int b) -> void {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            edges[p].emplace_back(a, b);
            tot++;
            return;
        }
        int m = (l + r) / 2;
        self(self, 2 * p, l, m, x, y, a, b);
        self(self, 2 * p + 1, m, r, x, y, a, b);
    };
    
    for (int i = 0; i < m; i++) {
        int a, b, l, r;
        std::cin >> a >> b >> l >> r;
        l--;
        a--;
        b--;
        work(work, 1, 0, n, l, r, a, b);
    }
    
    std::vector<int> lead(n);
    std::iota(lead.begin(), lead.end(), 0);
    std::vector<int> f(n);
    std::iota(f.begin(), f.end(), 0);
    std::vector<int> siz(n, 1);
    std::vector<i64> val(tot);
    std::vector<std::array<int, 2>> ch(tot);
    int cur = n;
    
    auto find = [&](int x)  {
        while (x != f[x]) {
            x = f[x];
        }
        return x;
    };
    
    std::vector<int> his;
    auto solve = [&](auto self, int p, int l, int r) -> void {
        int tm = his.size();
        for (auto [a, b] : edges[p]) {
            a = find(a);
            b = find(b);
            if (a == b) {
                continue;
            }
            if (siz[a] < siz[b]) {
                std::swap(a, b);
            }
            siz[a] += siz[b];
            f[b] = a;
            his.push_back(b);
            int u = cur++;
            ch[u] = {lead[a], lead[b]};
            lead[a] = u;
        }
        if (r - l == 1) {
            val[lead[find(0)]] += r;
        } else {
            int m = (l + r) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
        }
        while (his.size() > tm) {
            int b = his.back();
            his.pop_back();
            int a = f[b];
            siz[a] -= siz[b];
            f[b] = b;
            int u = lead[a];
            val[ch[u][0]] += val[u];
            val[ch[u][1]] += val[u];
            lead[a] = ch[u][0];
        }
    };
    solve(solve, 1, 0, n);
    
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        ans ^= val[i];
    }
    std::cout << ans << "\n";
    
    return 0;
}

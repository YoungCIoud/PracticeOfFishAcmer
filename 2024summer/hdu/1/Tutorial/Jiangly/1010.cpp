#include <bits/stdc++.h>

using i64 = long long;

template<class T,
    class Cmp = std::less<T>>
struct RMQ {
    const Cmp cmp = Cmp();
    static constexpr unsigned B = 64;
    using u64 = unsigned long long;
    int n;
    std::vector<std::vector<T>> a;
    std::vector<T> pre, suf, ini;
    std::vector<u64> stk;
    RMQ() {}
    RMQ(const std::vector<T> &v) {
        init(v);
    }
    void init(const std::vector<T> &v) {
        n = v.size();
        pre = suf = ini = v;
        stk.resize(n);
        if (!n) {
            return;
        }
        const int M = (n - 1) / B + 1;
        const int lg = std::__lg(M);
        a.assign(lg + 1, std::vector<T>(M));
        for (int i = 0; i < M; i++) {
            a[0][i] = v[i * B];
            for (int j = 1; j < B && i * B + j < n; j++) {
                a[0][i] = std::min(a[0][i], v[i * B + j], cmp);
            }
        }
        for (int i = 1; i < n; i++) {
            if (i % B) {
                pre[i] = std::min(pre[i], pre[i - 1], cmp);
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            if (i % B != B - 1) {
                suf[i] = std::min(suf[i], suf[i + 1], cmp);
            }
        }
        for (int j = 0; j < lg; j++) {
            for (int i = 0; i + (2 << j) <= M; i++) {
                a[j + 1][i] = std::min(a[j][i], a[j][i + (1 << j)], cmp);
            }
        }
        for (int i = 0; i < M; i++) {
            const int l = i * B;
            const int r = std::min(1U * n, l + B);
            u64 s = 0;
            for (int j = l; j < r; j++) {
                while (s && cmp(v[j], v[std::__lg(s) + l])) {
                    s ^= 1ULL << std::__lg(s);
                }
                s |= 1ULL << (j - l);
                stk[j] = s;
            }
        }
    } 
    T operator()(int l, int r) {
        if (l / B != (r - 1) / B) {
            T ans = std::min(suf[l], pre[r - 1], cmp);
            l = l / B + 1;
            r = r / B;
            if (l < r) {
                int k = std::__lg(r - l);
                ans = std::min({ans, a[k][l], a[k][r - (1 << k)]}, cmp);
            }
            return ans;
        } else {
            int x = B * (l / B);
            return ini[__builtin_ctzll(stk[r - 1] >> (l - x)) + l];
        }
    }
};

void solve() {
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    std::vector<std::pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        v[i] = {a[i], i};
    }
    
    
    RMQ<std::pair<int, int>, std::greater<>> rmq(v);
    
    std::vector<i64> cnt(n + 1);
    
    i64 out = 0;
    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        
        const int len = r - l;
        
        std::vector<int> s;
        auto work = [&](auto self, int l, int r) -> void {
            if (r - l <= len / 50) {
                return;
            }
            int m = rmq(l, r).second;
            cnt[a[m]] += 1LL * (r - m) * (m - l + 1);
            s.push_back(a[m]);
            self(self, l, m);
            self(self, m + 1, r);
        };
        work(work, l, r);
        
        i64 ans = 0;
        int v = 0;
        for (auto x : s) {
            if (cnt[x] > ans || (cnt[x] == ans && x > v)) {
                ans = cnt[x];
                v = x;
            }
            cnt[x] = 0;
        }
        out ^= 1LL * (i + 1) * v;
    }
    std::cout << out << "\n";
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

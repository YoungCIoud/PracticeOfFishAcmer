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
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7, MX = 1 << 20;
constexpr int N = 1e5, L = 20;

class LinearBasis {
    private:
        std::array<int, L> p;
    public:
        LinearBasis(): p{} {}
        bool insert(int x) {
            for (int i = L - 1; ~i && x; i--) {
                if (!(x >> i & 1)) {
                    continue;
                }

                if (p[i]) {
                    x ^= p[i];
                }
                else {
                    for (int j = i - 1; ~j; j--) {
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
                    break;
                }
            }
            return x != 0;
        }

        int& operator[](int i) {
            return p[i];
        }
};

i64 pw[N + 5];

void solve() {
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::vector a(n, 0ll);
    for (auto &i : a) {
        std::cin >> i;
    }

    std::vector qr(n, std::vector<std::pair<int, i64>>{});
    for (int i = 0; i < q; i++) {
        int l = 0;
        i64 x = 0;
        std::cin >> l >> x;
        l--;
        qr[l].push_back(std::make_pair(i, x));
    }

    LinearBasis lb;
    std::vector ans(q, 0ll);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (not lb.insert(a[i])) {
            cnt++;
        }

        for (auto &[id, x] : qr[i]) {
            for (int l = L - 1; ~l; l--) {
                if (x >> l & 1) {
                    x ^= lb[l];
                }
            }

            if (x == 0) {
                ans[id] = pw[cnt];
            }
        }
    }
    for (auto &i : ans) {
        std::cout << i << '\n';
    }
    return;
}

int main () {
    IOS;
    int _t = 1;
    //std::cin >> _t;
    
    pw[0] = 1;
    for (int i = 1; i <= N; i++) {
        pw[i] = pw[i - 1] << 1;
        if (pw[i] >= Mod) {
            pw[i] -= Mod;
        }
    }
    
    while (_t--) {
        solve();
    }

    return 0;
}
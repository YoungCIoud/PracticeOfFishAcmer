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

constexpr int Mod = 10086;
constexpr int N = 1e5, Inf = 1e9, L = 30;

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

void solve() {
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0ll);
    LinearBasis lb;
    for (auto &i : a) {
        std::cin >> i;
        lb.insert(i);
        assert(i <= Inf);
    }
    
    int q = 0;
    std::cin >> q;
    int rk = 0;
    for (int i = L - 1; ~i; i--) {
        int p = lb[i];
        if (p) {
            n--;
            rk <<= 1;
            // if (q >> i & 1) {
            //     rk |= 1;
            // }
            if (p <= q) {
                rk |= 1;
                q ^= p; // ^= but not -=
            }
        }
    }

    int ans = rk % Mod;
    for (int i = 0; i < n; i++) {
        ans <<= 1;
        if (ans >= Mod) {
            ans -= Mod;
        }
    }
    
    std::cout << (ans + 1) % Mod << '\n';

    return;
}

int main () {
    IOS;
    int _t = 1;
    //std::cin >> _t;
    
    while (_t--) {
        solve();
    }

    return 0;
}
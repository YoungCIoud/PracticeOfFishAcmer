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

constexpr i64 Mod = 1e9;
constexpr int N = 1e2, Inf = 1e9;

class LinearBasis {
    private:
        static constexpr int L = 60;
        std::array<i64, L> p;
    public:
        LinearBasis(): p{} {}
        bool insert(i64 x) {
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
                    return true;
                }
            }
            return false;
        }
};

void solve() {
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0);
    i64 sum = 0;
    for (auto &i : a) {
        std::cin >> i;
        sum += i;
    }

    std::sort(a.begin(), a.end(), std::greater<int>());
    LinearBasis lb;
    bool ok = false;
    for (auto &i : a) {
        if (lb.insert(i)) {
            sum -= i;
            ok = true;
        }
    }
    std::cout << (ok ? sum : -1ll) << '\n';
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

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

constexpr i64 Mod = 1e9, Inf = 1e18;
constexpr int N = 1e3, M = 1e4;

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
    std::vector a(n, std::pair<int, i64>{});
    for (auto &[magic, num] : a) {
        std::cin >> num >> magic;
    }
    std::sort(a.begin(), a.end(), std::greater<std::pair<int, i64>>());

    LinearBasis LB;
    int ans = 0;
    for (auto &[magic, num] : a) {
        if (LB.insert(num)) {
            ans += magic;
        }
    }
    std::cout << ans << '\n';
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
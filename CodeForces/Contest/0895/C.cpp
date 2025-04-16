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

int prime[L];
int rk[100];

void solve() {
    int n = 0;
    std::cin >> n;
    LinearBasis lb;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;

        int u = 0;
        for (int j = 0; j < L && a != 1; j++) {
            int l = 0;
            while (a % prime[j] == 0) {
                a /= prime[j];
                l++;
            }

            u |= (l & 1) << j;
        }
        if (not lb.insert(u)) {
            cnt++;
        }
    }

    int ans = 1;
    for (int i = 0; i < cnt; i++) {
        ans <<= 1;
        if (ans >= Mod) {
            ans -= Mod;
        }
    }
    std::cout << ans - 1 << '\n';
    return;
}

int main () {
    IOS;
    int _t = 1;
    //std::cin >> _t;
    
    int cnt = 0;
    for (int i = 2; i < 100; i++) {
        bool ok = true;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                ok = false;
                break;
            }
        }
        if (ok) {
            prime[cnt] = i;
            rk[i] = cnt;
            cnt++;
        }
    }
    
    while (_t--) {
        solve();
    }

    return 0;
}
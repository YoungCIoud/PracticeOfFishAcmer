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
constexpr int N = 1e6, K = 1e6;

void solve() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    if (k > n) {
        std::cout << 1 << '\n';
        return;
    }

    std::vector a(n + 1, 1);
    a[k] = k;
    for (int i = k, j = 0, sum = 2 * k; i < n; i++, j++) {
        sum -= a[j];
        if (sum < 0) {
            sum += Mod;
        }
        a[i + 1] = sum;
        sum += a[i + 1];
        if (sum >= Mod) {
            sum -= Mod;
        }
    }
    std::cout << a[n] << '\n';
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

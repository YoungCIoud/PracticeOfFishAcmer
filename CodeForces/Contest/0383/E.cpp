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

constexpr i64 Mod = 1e9 + 7, Inf = 1e18;
constexpr int N = 1e6, L = 24;

int f(std::string s) {
    int res = 0;
    for (auto &c : s) {
        res |= (1 << c - 'a');
    }
    return res;
}

int main () {
    int n = 0;
    std::cin >> n;
    std::vector cnt(1 << L, 0);
    std::string s;
    for (int i = 0; i < n; i++) {
        std::cin >> s;
        cnt[f(s)]++;
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < (1 << L); j++) {
            if (j >> i & 1) {
                cnt[j] += cnt[j ^ (1 << i)];
            }
        }
    }

    i64 ans = 0;
    for (int i = 0; i < (1 << L); i++) {
        ans ^= (n - cnt[i]) * (n - cnt[i]);
    }
    std::cout << ans << '\n';
    return 0;
}


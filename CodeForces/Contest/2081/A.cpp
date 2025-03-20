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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, MAX = 1e9; 
i64 p2[N + 5];
i64 p[N + 5]; // the probabilities of carry

i64 qpow(i64 a, i64 p) {
    i64 res = 1;
    while (p) {
        if (p & 1) {
            (res *= a) %= Mod;
        }

        (a *= a) %= Mod;
        p >>= 1;
    }
    return res;
}

i64 inv(i64 a) {
    return qpow(a, Mod - 2);
}


void solve() {
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    std::reverse(s.begin(), s.end());
    s.pop_back();
    n--;
    
    for (int l = 0, r = 1; l < n; l = r) {
        while (r < n && s[r] == s[l]) {
            r++;
        }

        int cnt = r - l;
        if (s[l] == '0') {
            p[r - 1] = p[l - 1] * p2[cnt] % Mod;
        }
        else {
            p[r - 1] = (Mod + 1 - p2[cnt]) * (Mod + 1 - p[l - 1]) % Mod + p[l - 1];
            if (p[r - 1] >= Mod) {
                p[r - 1] -= Mod;
            }
        }
    }
    std::cout << (n * (Mod + 1 - p[n - 1]) % Mod + (n + 1) * p[n - 1] % Mod) % Mod << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;

    p2[N] = inv(qpow(2ll, N));
    for (int i = N; i >= 1; i--) {
        p2[i - 1] = p2[i] * 2ll % Mod;
    }
    
    while (_t--)
    {
        solve();
    }

    return 0;
}

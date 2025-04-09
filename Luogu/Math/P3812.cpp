#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), \
                std::cin.tie(0), \
                std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 50, L = 50;

i64 p[L];

bool insert(i64 a) {
    for (int bit = L - 1; ~bit; bit--) {
        if (!(a >> bit & 1)) {
            continue;
        }

        if (p[bit]) {
            a ^= p[bit];
        }
        else {
            for (int b = 0; b < bit; b++) {
                if (a >> b & 1) {
                    a ^= p[b];
                }
            }
            for (int b = bit; b < L; b++) {
                if (p[b] >> bit & 1) {
                    p[b] ^= a;
                }
            }
            p[bit] = a;
            
            return (a != 0);
        }
    }
    return false;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        i64 a = 0;
        std::cin >> a;
        insert(a);
    }
    i64 res = 0;
    for (int i = 0; i < L; i++) {
        res ^= p[i];
    }
    std::cout << res << '\n';
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
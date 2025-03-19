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

constexpr u64 Mod = 1'0000'0000'0000'1029, MAX = -1;
constexpr int N = 5e5, Q = 5e5;

void solve() {
    // a1 ...10101
    // a2 ...01010
    unsigned a1 = 0, a2 = 0;
    for (int i = 0; i < 30; i++) {
        a1 <<= 1, a2 <<= 1;
        if (i & 1) {
            a1 |= 1;
        }
        else {
            a2 |= 1;
        }
    }
    unsigned q1 = 0, q2 = 0;
    std::cout << a1 << std::endl;
    std::cin >> q1;
    std::cout << a2 << std::endl;
    std::cin >> q2;

    unsigned int x = 0, y = 0;
    int c1 = 0, c2 = 0, d = 0;
    for (int i = 0; i < 30; i++) {
        if (i & 1) {
            int val = q1 >> d & 7;
            val -= c1;
            if (val == 2) c1 = 0;
            else c1 = 1;
            if (val >= 4) x |= 1 << i;
            if (val == 6) y |= 1 << i;
            d += 2;
        }
        else {
            int val = q2 >> d & 3;
            val -= c2;
            if (val >= 1) x |= 1 << i;
            if (val == 2) y |= 1 << i;
            c2 = 1;
        }
    }

    std::cout << '!' << std::endl;
    int m = 0;
    std::cin >> m;
    std::cout << (x | m) + (y | m) << std::endl;
    return;
}

int main()
{
   // IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }
    return 0;
}

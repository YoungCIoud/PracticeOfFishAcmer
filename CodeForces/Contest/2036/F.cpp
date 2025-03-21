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
constexpr int N = 2e5, MAX = 1e9;

i64 pre(i64 x) {
    if (x < 0) {
        return 0;
    }
    switch (x % 4) {
        case 0:
            return x;
        case 1:
            return 1;
        case 2:
            return x + 1;
        case 3:
            return 0;
    }
    return -1;
}


void solve() {
    i64 l = 0, r = 0;
    int i = 0, k = 0;
    std::cin >> l >> r >> i >> k;

    i64 sum = pre(r) ^ pre(l - 1);
    i64 ll = l >> i;
    if ((ll << i) + k < l) {
        ll++;
    }
    i64 rr = r >> i;
    if ((rr << i) + k > r) {
        rr--;
    }
    if (ll <= rr) {
        i64 sub = (pre(rr) ^ pre(ll - 1)) << i;
        if ((rr - ll + 1) & 1) {
            sub += k;
        }
        sum ^= sub;
    }
    std::cout << sum << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;

    while (_t--)
    {
        solve();
    }

    return 0;
}

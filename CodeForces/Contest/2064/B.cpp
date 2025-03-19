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
constexpr int N = 2e5, Q = 5e5;
int a[N + 5], cnt[N +5];

void solve() {
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        cnt[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        cnt[a[i]]++;
    }

    int L = 0, R = -1;
    int l = 0, r = -1;
    for (int i = 1; i <= n; i++) {
        if (cnt[a[i]] != 1) {
            if (r - l > R - L) {
                L = l, R = r;
            }
            l = 0, r = -1;
        }
        else if (l == 0) {
            l = r = i;
        }
        else {
            r++;
        }
    }
    if (r - l > R - L) {
        L = l, R = r;
    }

    if (L) {
        std::cout << L << ' ' << R << '\n';
    }
    else {
        std::cout << "0\n";
    }
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

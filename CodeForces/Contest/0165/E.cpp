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
constexpr int N = 1e6, M = 4e6, L = 24;

int a[N + 5];
i64 cnt[1 << L];

int find(int x) {
    for (int bit = 23; ~bit; bit--) {
        if (x >> bit & 1) {
            if (cnt[x ^ (1 << bit)]) {
                x ^= 1 << bit;
            }
        }
    }
    return x;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        cnt[a[i]]++;
    }

    for (int bit = 0; bit < L; bit++) {
        for (int i = 0; i < (1 << L); i++) {
            if (i >> bit & 1) {
                cnt[i] += cnt[i ^ (1 << bit)];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        a[i] ^= ((1 << L) - 1);
        if (cnt[a[i]] == 0) {
            std::cout << -1 << ' ';
        }
        else {
            std::cout << find(a[i]) << ' ';
        }
    }
    std::cout << '\n';
    return;
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
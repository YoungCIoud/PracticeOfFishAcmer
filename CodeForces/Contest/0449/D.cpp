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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e6, M = 1e6, L = 2;

int a[N + 5], num[N + 5];
i64 cnt[1 << L];
i64 p2[N + 5];

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        cnt[a[i]]++;
    }
    
    for (int bit = 0; bit < L; bit++) {
    }
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
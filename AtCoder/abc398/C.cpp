#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0), b(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        b[i] = a[i];
    }
    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());
    std::vector cnt(b.size(), 0);
    for (auto &i : a) {
        i = std::lower_bound(b.begin(), b.end(), i) - b.begin();
        cnt[i]++;
    }
    int mx = -2;
    for (int i = 0; i < n; i++) {
        if (cnt[a[i]] == 1 && (mx == -2 || a[mx] < a[i])) {
            mx = i;
        }
    }

    std::cout << mx + 1 << '\n';
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

    system("pause");

    return 0;
}
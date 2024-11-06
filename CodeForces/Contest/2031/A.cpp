#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    #define cout cout << ">>>\t"
#else
    #define debug(...)
    #define sp()
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
    std::vector a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
    }
    int mx = 1, cnt = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1]) {
            cnt++;
        }
        else {
            mx = std::max(mx, cnt);
            cnt = 1;
        }
    }
    std::cout << n - std::max(mx, cnt) << '\n';
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
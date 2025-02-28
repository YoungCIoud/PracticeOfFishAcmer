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

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0, x = 0;
    i64 k = 0;
    std::string s;
    std::cin >> n >> x >> k >> s;

    int p1 = n, p2 = n;
    for (int i = 0, d = 0; i < n; i++) {
        d += (s[i] == 'L' ? -1 : 1);
        if (d == -x && p1 == n) {
            p1 = i;
        }
        if (d == 0 && p2 == n) {
            p2 = i;
        }
    }

    i64 ans = 0;
    if (p1 != n && p1 < k) {
        p1++;
        k -= p1;
        ans = 1;

        if (p2 != n) {
            ans += k / (p2 + 1);
        }
    }
    std::cout << ans << '\n';
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

    sp();

    return 0;
}
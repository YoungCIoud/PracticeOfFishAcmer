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

std::vector<int> zfun(std::string s) {
    int n = s.length();
    std::vector z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r && z[i - l] < r - i + 1) {
            z[i] = z[i - l];
        }
        else {
            z[i] = std::max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}

void solve()
{
    std::string a, b;
    std::cin >> a >> b;
    auto z = zfun(b);
    z[0] = b.length();
    i64 ans = 0;
    for (int i = 0; i < b.length(); i++) {
        ans ^= 1ll * (i + 1) * (z[i] + 1);
    }
    std::cout << ans << '\n';

    z = zfun(b + "*" + a);
    ans = 0;
    for (int i = 1; i <= a.length(); i++) {
        ans ^= 1ll * i * (z[i + b.length()] + 1);
    }
    std::cout << ans << '\n';

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
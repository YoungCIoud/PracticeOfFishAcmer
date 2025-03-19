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
    int n = 0, q = 0;
    std::string s;
    std::cin >> n >> q >> s;
    int cnt = 0;
    for (auto &c : s) {
        if (c == '0') {
            cnt++;
        }
    }
    i64 pw = 935854081;
    for (int i = 0; i < n; i++) {
        (pw *= 2ll) %= Mod;
    }
    
    while (q--) {
        int pos = 0;
        std::cin >> pos;
        pos--;
        s[pos] ^= 1;
        if (s[pos] == '0') {
            cnt++;
        }
        else {
            cnt--;
        }

        i64 ans = (1ll * n * (n + 1) - 4ll * n * cnt + 4ll * cnt * cnt - 2);
        ans %= Mod;
        (ans *= pw) %= Mod;
        std::cout << ans << '\n';
    }
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
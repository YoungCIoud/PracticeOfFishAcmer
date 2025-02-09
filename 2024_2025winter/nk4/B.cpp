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
constexpr int N = 10, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    int tot = 0;
    for (auto &c : s) {
        if (c == '?') {
            tot++;
        }
    }

    int ans = 0;
    for (int i = 0; i < (1 << tot); i++) {
        std::string t = s;
        int tmp = i;
        for (auto &c : t) {
            if (c == '?') {
                c = (tmp & 1) + '0';
                tmp >>= 1;
            }
        }
        // std::cout << t << '\n';
        for (auto &c : t) {
            c ^= 1;

            int d = 0;
            for (int j = 0; j + 2 <= n; j++) {
                if (t.substr(j, 2) == "01") {
                    d++;
                }
                else if (t.substr(j, 2) == "10") {
                    d--;
                }
            }
            if (d == 0) {
                ans++;
            }

            c ^= 1;
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
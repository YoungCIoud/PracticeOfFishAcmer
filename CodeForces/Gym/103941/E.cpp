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
    int n = 0;
    std::cin >> n;
    std::vector pre(n + 1, std::array<int, 26>{});
    std::string s;
    std::cin >> s;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            pre[i + 1][j] = pre[i][j];
        }
        pre[i + 1][s[i] - 'a']++;
    }

    int l = 0, r = n + 1;
    int lc = '\000', rc = '\000';
    while (l < n && lc == '\000') {
        l++;
        for (int i = 0; i < 26; i++) {
            if (pre[l][i] == 5) {
                lc = 'a' + i;
                break;
            }
        }
    }
    while (r > 1 && rc == '\000') {
        r--;
        for (int i = 0; i < 26; i++) {
            if (pre[n][i] - pre[r - 1][i] == 5) {
                rc = 'a' + i;
                break;
            }
        }
    }

    char mc = '\000';
    if (l < r) {
        for (int i = 0; i < 26; i++) {
            if (pre[r - 1][i] - pre[l][i] >= 7) {
                mc = 'a' + i;
                break;
            }
        }
    }

    if (lc && mc && rc) {
        std::cout << std::string(5, lc) + std::string(7, mc) + std::string(5, rc) << '\n';
    }
    else {
        std::cout << "none\n";
    }
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
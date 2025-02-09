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
constexpr int N = 1e6, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n;
    std::cin >> s;
    std::vector ans(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        ans[i] += (n + i - 1) / i; // n / i 向上取整
    }

    for (int l = 0, r = 0; l < n; l = r) {
        while (r < n && s[l] == s[r]) {
            r++;
        }
        int len = r - l;
        for (int k = 1; k <= len; k++) {
            int ll = (l + k - 1) / k * k;
            ans[k] -= (r - ll) / k;
            if (r == n && (r - ll) % k != 0) {
                ans[k]--;
            }
        }
        if (r == n) {
            for (int k = len + 1; k <= n; k++) {
                if ((l + k - 1) / k * k < r) {
                    ans[k]--;
                }
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        res ^= ans[i];
    }
    std::cout << res << '\n';
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
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

std::string hash(std::string s) {
    int n = s.size();
    std::vector suf(n, 0), fst(26, 0);
    suf[n - 1] = 1;
    fst[s[n - 1] - 'a'] =  n - 1;
    for (int i = n - 2; i >= 0; i--) {
        suf[i] += suf[i + 1];
        if (fst[s[i] - 'a'] == 0) {
            suf[i] += 1;
            fst[s[i] - 'a'] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        s[i] = 'a' + suf[fst[s[i] - 'a']] - 1;
    }
    return s;
}

void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    std::string ans = "";
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, hash(s.substr(0, i)));
    }
    std::cout << ans << '\n';
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
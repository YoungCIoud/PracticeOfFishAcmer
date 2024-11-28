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
    std::string s;
    std::cin >> n >> s;
    std::vector pre(n + 1, 0ull);
    for (int i = 1; i <= n; i++) {
        int num = s[i - 1] - '0';
        pre[i] = i * num;
        pre[i] += pre[i - 1];
    }
    std::string ans;
    u64 cnt = 0;
    for (int i = n; i >= 1; i--) {
        cnt += pre[i];
        ans += cnt % 10ull + '0';
        cnt /= 10;
    }
    if (cnt != 0) {
        std::cout << cnt;
    }
    std::reverse(ans.begin(), ans.end());
    std::cout << ans << '\n';
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
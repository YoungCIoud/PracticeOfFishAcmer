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
constexpr int N = 2e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0, m = 0, v = 0;
    std::cin >> n >> m >> v;
    std::vector a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> p_id(1, 0);
    for (int i = 1, sum = 0; i <= n; i++) {
        sum += a[i];
        if (sum >= v) {
            p_id.push_back(i);
            sum = 0;
        }
    }
    std::vector<int> s_id(1, n);
    for (int i = n, sum = 0; i >= 0; i--) {
        sum += a[i];
        if (sum >= v) {
            s_id.push_back(i - 1);
            sum = 0;
        }
    }
    std::vector pre(n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }

    if (p_id.size() <= m && s_id.size() <= m) {
        std::cout << "-1\n";
        return;
    }
    
    i64 ans = 0ll;
    for (int i = 0; i <= m; i++) {
        ans = std::max(ans, pre[s_id[m - i]] - pre[p_id[i]]);
    }
    std::cout << ans << '\n';
    return;
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
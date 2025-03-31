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

i64 a[N + 5];
std::vector<int> g[N + 5];

int ans;
void dfs(int cur, i64 gcd) {
    if (g[cur].empty()) {
        if (__builtin_popcount(gcd) <= 1) {
            ans++;
        }
        return;
    }

    for (auto &to : g[cur]) {
        dfs(to, std::__gcd(gcd, std::abs(a[to] - a[cur])));
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 2; i <= n; i++) {
        int f = 0;
        std::cin >> f;
        g[f].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    ans = 0;
    dfs(1, 0);
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
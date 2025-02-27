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
constexpr int N = 2e5, M = 1e5, Inf = 1e9;
std::vector<int> g[N + 5];
std::vector f(N + 5, std::array<int, 2>{ -1, 1 });

void dfs(int cur, int fa = 0) {
    std::priority_queue<int> q;
    int mx = 0;
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }
        
        dfs(to, cur);
        q.push(-f[to][1]);
        mx = std::max(mx, f[to][1]);
    }
    if (mx > 1) {
        f[cur][0] = mx + 1;
    }
    
    while (q.size() > 4) {
        q.pop();
    }
    int mn = 0;
    if (q.size() == 4) {
        mn = -q.top();
        q.pop();
    }
    if (q.size() == 3) {
        int sum = 0;
        while (not q.empty()) {
            sum -= q.top();
            q.pop();
        }
        f[cur][1] = sum + 1;
        
        if (mn > 0) {
            f[cur][0] = sum + mn + 1;
        }
    }

}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);
    int ans = -1;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, f[i][0]);
    }
    std::cout << ans << '\n';
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
#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), \
                std::cin.tie(0), \
                std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 5e5;

std::vector<int> g[N + 5];
i64 ans;
int cnt[2], f[N + 5][2];

i64 C(int x) {
    return 1ll * x * (x - 1) / 2ll;
}

void dfs(int cur, int fa, int d) {
    ans += 6ll * cnt[d];
    ans += 6ll * C(cnt[d]);

    cnt[d]++;
    i64 c00 = 0, c11 = 0, c10 = 0;
    for (auto to : g[cur]) {
        int l = 0;
        if (to < 0) {
            to = -to;
            l = 1;
        }
        if (to == fa) {
            continue;
        }
        
        dfs(to, cur, d ^ l);
        c00 += 1ll * f[cur][0] * f[to][0];
        c10 += 1ll * f[cur][1] * f[to][0] + 1ll * f[cur][0] * f[to][1];
        c11 += 1ll * f[cur][1] * f[to][1];

        f[cur][0] += f[to][0];
        f[cur][1] += f[to][1];
    }

    f[cur][d]++;
    if (d) {
        ans += 6ll * (c00 + c10);
    }
    else {
        ans += 6ll * (2ll * c00 + c11);
    }

    return;
}

void solve()
{
    int n = 0;
    std::cin >> n;

    ans = n;
    cnt[0] = cnt[1] = 0;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        f[i][0] = f[i][1] = 0;
    }
    for (int i = 1; i < n; i++) {
        int u = 0, v = 0, w = 0;
        std::cin >> u >> v >> w;
        w %= 2;
        g[u].push_back(w ? -v : v);
        g[v].push_back(w ? -u : u);
    }

    dfs(1, 0, 0);
    std::cout << ans << '\n';

    return;
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
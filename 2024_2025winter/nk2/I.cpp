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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, M = 1e9, Inf = 1e9, L = 30;
std::vector<int> a(N + 5), g[N + 5];
i64 f[N + 5], cnt[N + 5][L][2], num[N + 5];

void dfs(int cur, int fa) {
    f[cur] = 0, num[cur] = 1;
    for (int i = 0; i < L; i++) {
        cnt[cur][i][a[cur] >> i & 1] = 1;
    }
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }
        dfs(to, cur);
        (f[cur] += f[to] * num[cur] + f[cur] * num[to]) %= Mod;
        for (int i = 0; i < L; i++) {
            (f[cur] += ((cnt[cur][i][0] * cnt[to][i][1] + cnt[cur][i][1] * cnt[to][i][0]) % Mod << i)) %= Mod;
            (cnt[cur][i][0] += cnt[cur][i][0] * num[to] + cnt[to][i][0] * num[cur]) %= Mod;
            (cnt[cur][i][1] += cnt[cur][i][1] * num[to] + cnt[to][i][1] * num[cur]) %= Mod;
        }
        (num[cur] += num[cur] * num[to]) %= Mod;
        debug("%d:\t%d\n", to, f[cur]);
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);
    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        (ans += f[i]) %= Mod;
    }
    std::cout << (ans << 1) % Mod << '\n';
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

/*
3
5 2 1
1 2
1 3

50


3
2 5 1
1 2
2 3


4
5 6 3 1
1 2
1 3
2 4

142
*/
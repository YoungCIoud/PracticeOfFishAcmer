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
std::vector<int> g[N + 5];
std::vector<int> v(N + 5); // 能到达最浅深度的儿子
std::vector<i64> p(N + 5); // 每个节点的概率
std::vector<int> pa(N + 5);
std::vector<i64> inv(N + 5);
void init(int n = 0) {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
}

int dfs(int cur, int fa = 0, int dep = 0) {
    v[cur] = 0;
    p[cur] = 0;
    pa[cur] = fa;
    int mn = N + 5;
    for (auto &to : g[cur]) {
        if (fa == to) {
            continue;
        }
        int t = dfs(to, cur, dep + 1);
        if (t < mn) {
            mn = t;
            v[cur] = to;
        }
    }

    return (cur != 1 && g[cur].size() == 1) ? dep : mn;
}

void count(int cur, i64 p0, int dep = 1) {
    if (v[cur] == 0) {
        return;
    }
    count(v[cur], p0, dep + 1);
    p[cur] = (p0 + p[v[cur]] * dep) % Mod * inv[dep + 1] % Mod;
    for (auto &to : g[cur]) {
        if (to != pa[cur] && to != v[cur]) {
            count(to, p[cur]);
        }
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;
    init(n);
    for (int i = 1; i <= n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    p[1] = 1;
    count(v[1], 1);
    for (auto &to : g[1]) {
        if (to != v[1]) {
            count(to, 1ll);
        }
    }

    for (int i = 1; i <= n; i++) {
        std::cout << p[i] << " \n"[i == n];
    }
}

int main()
{
    for (int i = 2; i <= N; i++) {
        int m = Mod - 2;
        inv[i] = 1;
        i64 a = i;
        for (; m; m >>= 1, a = a * a % Mod) {
            if (m & 1) {
                inv[i] = inv[i] * a % Mod;
            }
        }
    }

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
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
constexpr int N = 5e3, M = 1e5, Inf = 1e9;
int n;
std::vector<int> g[N + 1];
i64 C[N + 1][N + 1]; // 组合数
i64 cnt[N + 1]; // 子树 i 的拓扑排序数量
i64 fac[N + 1]; // 阶乘
int siz[N + 1]; // 以 i 为根的子树的大小
i64 dp[N + 1][N + 1]; // dp[i][j] 编号为 i 的节点排第 j 位且不考虑子树 i 内的拓扑排序的方案数

int qpow(i64 a, i64 p) {
    i64 res = 1;
    for (; p; a = a * a % Mod, p >>= 1) {
        if (p & 1) {
            (res *= a) %= Mod;
        }
    }
    return res;
}
int inv(i64 a) {
    return qpow(a, Mod - 2);
}

i64 init(int cur) {
    siz[cur] = 1;
    i64 inv_mul = 1;
    for (auto &to : g[cur]) {
        (inv_mul *= init(to)) %= Mod;
        siz[cur] += siz[to];
    }
    (inv_mul *= inv(siz[cur])) %= Mod;
    // 子树 cur 的拓扑排序的数量 siz[cur]! * inv_mul;
    cnt[cur] = fac[siz[cur]] * inv_mul % Mod;
    return inv_mul;
}

void dfs(int cur, int fa, int deep) {
    i64 num = cnt[fa] * inv(C[siz[fa] - 1][siz[cur]] * cnt[cur] % Mod) % Mod;
    for (int pos = deep; pos + siz[cur] <= n + 1; pos++) {
        // num 在子树 fa 内去掉子树 cur 后所得的树的拓扑排序的数量
        // num * C[siz[fa] - 1][siz[cur]] * cnt[cur] = cnt[fa]
        if (dp[fa][pos - 1] != 0) {
            dp[cur][pos] = dp[fa][pos - 1] * C[n - (pos - 1) - siz[cur]][siz[fa] - 1 - siz[cur]] % Mod * num % Mod;
        }
        (dp[cur][pos] += dp[cur][pos - 1]) %= Mod;
    }
    for (auto &to : g[cur]) {
        dfs(to, cur, deep + 1);
    }
    return;
}

void solve()
{
    std::cin >> n;
    for (int i = 2; i <= n; i++) {
        int fa = 0;
        std::cin >> fa;
        g[fa].push_back(i);
    }
    // 组合数 && 阶乘
    fac[0] = 1, C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = (fac[i - 1] * i) % Mod;
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod;
        }
    }
    init(1);
    dp[1][1] = 1;
    for (auto &to : g[1]) {
        dfs(to, 1, 2);
    }

    for (int i = 1; i <= n; i++) {
        std::cout << dp[i][i] * C[n - i][siz[i] - 1] % Mod * cnt[i] % Mod << " \n"[i == n];
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
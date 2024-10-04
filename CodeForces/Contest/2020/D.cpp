#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 2e5, M = 2e5, D = 10;
int fa[N + 5];
int getfa(int u) {
    return fa[u] == u ? u : (fa[u] = getfa(fa[u]));
}
// 将v并到u
void merge(int u, int v) {
    fa[getfa(v)] = getfa(u);
}

int id[N + 5][D + 5], dp[N + 5][D + 5], st[N + 5][D + 5], ed[N + 5][D + 5];
void init(int n = 0) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        for (int j = 1; j <= D; j++) {
            id[i][j] = i;
            dp[i][j] = 0;
            st[i][j] = ed[i][j] = 0;
        }
    }
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    init(n);
    for (int i = 1; i <= m; i++) {
        int a = 0, d = 0, k = 0;
        std::cin >> a >> d >> k;
        st[a][d]++;
        ed[a + k * d][d]++;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= D; j++) {
            dp[i][j] = st[i][j] - ed[i][j];

            if (i <= j ) {
                continue;
            }
            if (dp[i - j][j]) {
                dp[i][j] += dp[i - j][j];
                id[i][j] = id[i - j][j];
                merge(id[i][j], i);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (fa[i] == i) {
            ans++;
        }
    }
    std::cout << ans << '\n';
}

int main()
{
    // IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
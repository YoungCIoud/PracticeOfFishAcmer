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
constexpr int N = 1e3, M = 8e2, Inf = 1e9;

std::vector<std::array<i64, 3>> e;
int fa[M + 5];
int get(int u) {
    return fa[u] == u ? u : (fa[u] = get(fa[u]));
}
bool merge(int u, int v) {
    int fu = get(u);
    int fv = get(v);
    fa[fu] = fv;
    return fu != fv;
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector p(m, std::array<int, 2>{});
    for (auto &[u, v] : p) {
        std::cin >> u >> v;
    }
    for (int i = 0; i < m; i++) {
        e.push_back({ i, m, 4ll * p[i][0] * p[i][0] });
        e.push_back({ i, m + 1, 4ll * (n - p[i][0]) * (n - p[i][0]) });
        for (int j = i + 1; j < m; j++) {
            e.push_back({ i, j, 1ll * (p[i][0] - p[j][0]) * (p[i][0] - p[j][0]) + 1ll * (p[i][1] - p[j][1]) * (p[i][1] - p[j][1])});
        }
    }
    std::sort(e.begin(), e.end(),
    [](const auto &u, const auto &v) -> bool { return u[2] < v[2]; });

    for (int i = 0; i < m + 2; i++) {
        fa[i] = i;
    }
    for (auto &[u, v, d] : e) {
        if (merge(u, v) && get(m) == get(m + 1)) {
            std::cout << std::fixed << std::setprecision(2) << sqrt(double(d)) / 2.0 << '\n';
            return;
        }
    }
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
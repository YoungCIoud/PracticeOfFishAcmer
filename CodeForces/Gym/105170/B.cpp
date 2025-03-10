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

// #define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, M = 1e5, Inf = 1e9 + 10;
std::vector<int> g[N + 1], a(N + 1, 0);

std::array<i64, 3> dfs(int cur, int fa) {
    int siz = 1;

    std::vector<std::array<i64, 2>> obb, eve;
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        auto [v0, v1, sizt] = dfs(to, cur);
        if (sizt & 1) {
            obb.push_back({ v0, v1 });
        }
        else {
            eve.push_back({ v0, v1 });
        }
        siz += sizt;
    }

    i64 v0 = 0, v1 = 0;
    if (obb.size() == 0) {
        for (auto &[vv0, vv1] : eve) {
            v0 += vv1, v1 += vv0;
        }
    }
    else {
        // 大小为偶数子树可以任选两个值
        for (auto &[vv0, vv1] : eve) {
            v0 += std::max(vv0, vv1);
        }
        v1 = v0;

        i64 tmp = 0;
        for (auto &[vv0, vv1] : obb) {
            tmp += vv0;
        }
        std::sort(obb.begin(), obb.end(), [](auto &u, auto &v) {
            return u[1] - u[0] > v[1] - v[0];
        });

        for (int i = 0; i + i < obb.size(); i++) {
            tmp += obb[i][1] - obb[i][0];
        }
        
        v1 += tmp, v0 += tmp;
        if (obb.size() & 1) {
            int m = obb.size() >> 1;
            v1 += obb[m][0] - obb[m][1];
        }
    }
    
    return { v0 + a[cur], v1, siz };
}

void solve() {
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        g[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::cout << dfs(1, 0)[1] << '\n';
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
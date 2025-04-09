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
constexpr int N = 1e6, M = 1e4, Inf = 1e9;

bool vis[M + 5];
int fa[M + 5];
int find(int u) {
    return fa[u] == u ? u : (fa[u] = find(fa[u]));
}
void merge(int u, int v) {
    int fu = find(u);
    int fv = find(v);
    if (fu > fv) {
        std::swap(fu, fv);
    }
    if (fu == fv) {
        vis[fu] = true;
    }
    else {
        vis[fu] = true;
        fa[fu] = fv;
    }
    return;
}

void solve()
{
    for (int i = 1; i <= M; i++) {
        fa[i] = i;
    }

    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        merge(u, v);
    }
    for (int i = 1; i <= n + 1; i++) {
        if (not vis[i]) {
            std::cout << i - 1 << '\n';
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
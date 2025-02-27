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

int fa[N + 5];

int get(int u) {
    return (fa[u] == u ? u : (fa[u] = get(fa[u])));
}

// u <- v
bool merge(int u, int v) {
    int fv = get(v), fu = get(u);
    fa[fv] = fu;
    return fv != fu;
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }

    std::vector<std::array<int, 2>> e;
    for (int i = 1; i <= m; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        if (not merge(u, v)) {
            e.push_back({ i, u });
        }
    }

    std::set<int> root;
    for (int i = 1; i <= n; i++) {
        if (fa[i] == i) {
            root.insert(i);
        }
    }
    std::cout << root.size() - 1 << '\n';
    for (auto &[idx, v] : e) {
        if (root.size() == 1) {
            break;
        }
        root.erase(get(v));
        std::cout << idx << ' ' << v << ' ' << (*root.begin()) << '\n';
        merge((*root.begin()), v);
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
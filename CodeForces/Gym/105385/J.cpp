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
constexpr int N = 1e3, M = 1e6, Inf = 1e9;

struct Edge {
    int u, v, w;
    bool operator<(const Edge &a) const {
        return w > a.w;
    }
};

std::vector<int> e[N + 5], fa(N + 5);
void init(int n = 0) {
    for (int i = 0; i < n; i++) {
        e[i].clear();
        fa[i] = i;
    }
}

int getfa(int u) {
    return u == fa[u] ? u : fa[u] = getfa(fa[u]);
}
bool merge(int u, int v) {
    int fu = getfa(u), fv = getfa(v);
    fa[fu] = fv;
    return fu != fv;
}
void solve()
{
    int n = 0;
    std::cin >> n;
    init(n);
    std::vector a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
        i--;
    }

    std::priority_queue<Edge> q;
    for (int i = 0; i < n; i++) {
        int w = 0;
        for (int j = 0; j < i; j++) {
            std::cin >> w;
            q.push({ i, j, w });
            e[i].push_back(w);
            e[j].push_back(w);
        }
        std::cin >> w;
        e[i].push_back(w);

        for (int j = i + 1; j < n; j++) {
            std::cin >> w;
        }
    }

    int cnt = 0;
    i64 ans = 0;
    while (not q.empty()) {
        auto [u, v, w] = q.top();
        q.pop();
        if (merge(u, v)) {
            ans += w;
            cnt++;
        }
        if (cnt == n - 1) {
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {
            ans += 1ll * a[i] * (*std::min_element(e[i].begin(), e[i].end()));
        }
    }
    std::cout << ans << '\n';
}

int main()
{
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
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
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9;
constexpr int N = 2e5, M = 3e5;

class DSU {
    private:
        int n, cnt;
        std::vector<int> fa;
    public:
        DSU (int n): n(n), cnt(n) {
            fa.assign(n + 1, 0);
            std::iota(fa.begin(), fa.end(), 0);
        }

        int get(int u) {
            return fa[u] == u ? u : (fa[u] = get(fa[u]));
        }

        bool merge(int u, int v) {
            int fu = get(u), fv = get(v);
            fa[fv] = fu;
            if (fv != fu) {
                cnt--;
                return true;
            }
            return false;
        }

        int num() {
            return cnt;
        }
};

std::vector<int> g[N + 5];

void solve() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    DSU con(n);
    std::vector ans(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        std::sort(g[i].begin(), g[i].end());
        for (auto &to : g[i]) {
            if (to < i) {
                con.merge(to, i);
            }
            else {
                break;
            }
        }

        ans[i] = con.num() == n - i + 1 ? 0 : -1;
    }

    std::set<std::pair<int, int>> kep, del;
    for (int i = 1; i <= n; i++) {
        if (not g[i].empty()) {
            kep.insert(std::make_pair(g[i][0], i));
        }
    }

    for (int i = 1; i < n; i++) {
        if (not g[i].empty()) {
            if (kep.count(std::make_pair(g[i][0], i))) {
                kep.erase(std::make_pair(g[i][0], i));
            }
            else {
                del.erase(std::make_pair(g[i][0], i));
            }
        }
        if (ans[i] == -1) {
            continue;
        }
        
        while (not kep.empty() && (*kep.begin()).first <= i) {
            del.insert(*kep.begin());
            kep.erase(kep.begin());
        }
        ans[i] = del.size();
    }

    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << '\n';
    }
    
    return;
}

int main () {
    IOS;
    int _t = 1;
    //std::cin >> _t;
    
    while (_t--) {
        solve();
    }

    return 0;
}

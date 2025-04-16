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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 2e5;

std::vector<int> g[N + 5];

int D[N + 5]; // max distance to leave
int mx1[N + 5], mx2[N + 5]; // index
int up[N + 5]; // length
void dfs1(int cur, int fa) {
    mx1[cur] = mx2[cur] = D[cur] = 0;
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }
        dfs1(to, cur);

        if (D[to] + 1 > D[cur]) {
            D[cur] = D[to] + 1;
            mx2[cur] = mx1[cur];
            mx1[cur] = to;
        }
        else if (D[to] >= D[mx2[cur]]) {
            mx2[cur] = to;
        }
    }
    return; 
}
void dfs2(int cur, int fa) {
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }
        
        up[to] = 0;
        if (mx1[cur] != to) {
            up[to] = D[cur] + 1;
        }
        else if (mx2[cur]) {
            up[to] = D[mx2[cur]] + 2;
        }
        up[to] = std::max(up[to], up[cur] + 1);


        dfs2(to, cur);
    }
    return;
}

std::vector<int> getd(int n) {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    
    std::vector<int> res(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        res[i] = std::max(up[i], D[i]);
        res[0] = std::max(res[0], up[i] + D[i]);
    }
    std::sort(res.begin(), res.end());
    return res;
}

void solve() {
    std::array<int, 2> n{};
    std::array<std::vector<int>, 2> d{};
    std::cin >> n[0];
    d[0] = getd(n[0]);
    std::cin >> n[1];
    d[1] = getd(n[1]);

    int dia = std::max(d[0][n[0]], d[1][n[1]]);
    i64 ans = 0, cnt = 0, cntd = 0;
    for (int u = 0; u < 2; u++) {
        int v = u ^ 1;
        for (int i = 0; i < n[u]; i++) {
            int m = std::upper_bound(d[v].begin(), d[v].end() - 1, dia - d[u][i] - 1) - d[v].begin();
            ans += 1ll * (n[v] - m) * d[u][i];
            cnt += n[v] - m;
            cntd += m;
        }
    }

    assert(!(cnt & 1));
    ans += (cnt >> 1);
    ans += 1ll * dia * (cntd >> 1);
    std::cout << ans << '\n';
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

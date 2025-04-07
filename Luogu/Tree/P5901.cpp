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
constexpr int N = 2e5, R = 2.5e4, Q = 2e5, Inf = 1e9, L = 450; // sqrt(N);

std::vector<int> g[N + 5];
int col[N + 5], num[R + 5], h[R + 5], cnt;

unsigned uBig[L][R + 5], vBig[R + 5][L];

int above[L]; // 统计祖先中的大点
int below[L]; // 利用差值统计子树中的大点
int siz[N + 5], dfn[N + 5], tim;
int fst[R + 5], jump[N + 5];
void dfs(int cur) {
    dfn[++tim] = cur;
    siz[cur] = 1;
    if (h[col[cur]]) {
        above[h[col[cur]]]++;
        below[h[col[cur]]]++;
    }
    else {
        for (int i = 1; i <= cnt; i++) {
            vBig[col[cur]][i] -= below[i];
        }
    }
    for (int i = 1; i <= cnt; i++) {
        uBig[i][col[cur]] += above[i];
    }

    for (int i = 0; i < g[cur].size(); i++) {
        dfs(g[cur][i]);
        siz[cur] += siz[g[cur][i]];
    }

    if (h[col[cur]]) {
        above[h[col[cur]]]--;
    }
    else {
        for (int i = 1; i <= cnt; i++) {
            vBig[col[cur]][i] += below[i];
        }
    }

    return;
}

void solve()
{
    int n = 0, r = 0, q = 0;
    std::cin >> n >> r >> q;
    std::cin >> col[1];
    for (int i = 2; i <= n; i++) {
        int fa = 0;
        std::cin >> fa >> col[i];
        g[fa].push_back(i);
        num[col[i]]++;
    }
    for (int i = 1; i <= r; i++) {
        if (num[i] * num[i] >= n) {
            h[i] = ++cnt;
        }
    }
    
    dfs(1);
    for (int i = 1; i <= r; i++) {
        fst[i] = Inf;
    }
    for (int i = n; i; i--) {
        jump[i] = fst[col[dfn[i]]];
        fst[col[dfn[i]]] = i;
    }

    while (q--) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        unsigned ans = 0;
        if (h[u]) {
            ans = uBig[h[u]][v];
        }
        else if (h[v]) {
            ans = vBig[u][h[v]];
        }
        else {
            int add = 0;
            std::stack<int> R;
            int pu = fst[u]; // pending
            int pv = fst[v]; // now
            while (pv != Inf) {
                while (pv > pu) {
                    if (pv < pu + siz[dfn[pu]]) {
                        R.push(pu + siz[dfn[pu]]);
                        add++;
                    }
                    pu = jump[pu];
                }
                ans += add;
                pv = jump[pv];
                while (not R.empty() && R.top() <= pv) {
                    R.pop();
                    add--;
                }
            }
        }
        std::cout << ans << std::endl;
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
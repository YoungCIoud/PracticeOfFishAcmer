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
constexpr int N = 1e5, M = 1e5;
int n;
std::vector<int> g[N + 5], dep[N + 5];

int tot;
std::array<int, 3> qr[N + 5]; 
int tim, L[N + 5], R[N + 5];

void dfs(int cur, int fa = 0, int dp = 1) {
    dep[dp].push_back(cur);
    L[cur] = ++tim;
    for (auto &to : g[cur]) {
        if (to == fa) {
            continue;
        }

        dfs(to, cur, dp + 1);
    }
    R[cur] = tim;
}

int tr[N + 5];

int lowbit(int x) {
    return x & -x;
}

void add(int pos) {
    while (pos <= n) {
        tr[pos]++;
        pos += lowbit(pos);
    }
    return;
}

int ask(int pos) {
    int res = 0;
    while (pos > 0) {
        res += tr[pos];
        pos -= lowbit(pos);
    }
    return res;
}

void solve() {
    int m = 0;
    std::cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);

    for (int i = 0, lst = n + 1; i < m; i++) {
        int op = 0, x = 0;
        std::cin >> op >> x;
        if (op == 1) {
            lst = x;
        }
        else {
            qr[tot] = { tot, lst, x };
            tot++;
        }
    }
    // 染色深度深的在前面，这样对于后续的操作的是加法
    sort(qr, qr + tot,
            [] (auto &u, auto& v) -> bool { return u[1] > v[1]; });

    int done = n + 1;
    std::vector ans(tot, 0);
    for (int i = 0; i < tot; i++) {
        for (int d = qr[i][1]; d < done; d++) {
            for (auto &v : dep[d]) {
                add(L[v]);
            }
        }
        done = qr[i][1];
        ans[qr[i][0]] = ask(R[qr[i][2]]) - ask(L[qr[i][2]] - 1);
    }

    for (auto &i : ans) {
        std::cout << i << '\n';
    }

    return;
}

int main()
{
    IOS;
    int _t = 1;
//    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}

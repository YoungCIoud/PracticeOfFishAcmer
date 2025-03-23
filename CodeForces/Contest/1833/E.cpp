#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, M = 1e5, Inf = 1e9;

int fa[N + 5], nei[N + 5];
bool locked[N + 5];
int find(int u) {
    return u == fa[u] ? u : (fa[u] = find(fa[u]));
}
void merge(int u, int v) {
    fa[find(v)] = find(u);
}

void upd(int u, int v) {
    if (nei[u] == 0) {
        nei[u] = v;
    }
    else if (v != nei[u]) {
        nei[u] = -1;
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        nei[i] = 0;
        locked[i] = true;
    }
    for (int i = 1; i <= n; i++) {
        int a = 0;
        std::cin >> a;
        merge(i, a);
        upd(a, i);
        upd(i, a);
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (nei[i] != -1) {
            locked[find(i)] = false;
        }
        if (fa[i] == i) {
            cnt++;
        }
    }
    int mx = cnt;
    for (int i = 1; i <= n; i++) {
        if (fa[i] == i && not locked[i]) {
            cnt--;
        }
    }
    int mn = cnt + (mx != cnt);
    std::cout << mn << ' ' << mx << '\n';
    return;
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

    system("pause");

    return 0;
}
#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    // #define cout cout << ">>>\t"
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 5e5, M = 1e5, Inf = 1e9;
int fa[N + 5], mx[N + 5], a[N + 5];
void init(int n = 0) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        mx[i] = a[i];
    }
}

int getfa(int u) {
    return fa[u] == u ? u : fa[u] = getfa(fa[u]);
}
// u 合并到 v 上 
void merge(int u, int v) {
    fa[getfa(u)] = getfa(v);
}
void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    init(n);
    std::stack<int> rt;
    for (int i = 1; i <= n; i++) {
        int val = a[i];
        while (!rt.empty() && mx[rt.top()] > a[i]) {
            int lst = rt.top();
            rt.pop();
            merge(lst, i);
            val = std::max(val, mx[lst]);
        }
        rt.push(i);
        mx[i] = val;
    }
    for (int i = 1; i <= n; i++) {
        std::cout << mx[getfa(i)] << " \n"[i == n];
    }
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
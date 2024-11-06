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
constexpr int N = 1e6, M = 1e5, Inf = 1e9;
std::vector<int> g[N];
void init(int n = 0) {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
}

int dfs(int cur) {
    std::priority_queue<int> q;
    for (auto &to : g[cur]) {
        q.push(-dfs(to));
    }
    if (q.empty()) {
        return 1;
    }
    else if (q.size() == 1) {
        return -q.top() + 1;
    }
    else {
        while (q.size() > 2) {
            q.pop();
            q.push(q.top() - 1);
            q.pop();
        }
        q.pop();
        return -q.top() + 1;
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;
    init(n);
    for (int i = 2; i <= n; i++) {
        int p = 0;
        std::cin >> p;
        g[p].push_back(i);
    }
    std::cout << dfs(1) - 1 << '\n';
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
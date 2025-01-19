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
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector idx(n + 1, 0);
    std::vector q(n + 1, std::priority_queue<std::pair<int, int>>{});
    for (int i = 1; i <= n; i++) {
        idx[i] = i;
        int l = 0, r = 0;
        std::cin >> l >> r;
        q[l].push({ -r, i });
    }

    // 将 q[v] 合并到 q[u] 上
    auto merge = [&](int u, int v) -> void {
        while (not q[v].empty()) {
            q[u].push(q[v].top());
            q[v].pop();
        }
        return;
    };

    bool ok = true;
    std::vector ans(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (q[idx[i]].empty()) {
            ok = false;
            break;
        }
        ans[q[idx[i]].top().second] = i;
        q[idx[i]].pop();

        if (not q[idx[i]].empty()) {
            if (i + q[idx[i]].top().first >= 0) {
                ok = false;
                break;
            }
            else if (q[idx[i]].size() > q[i + 1].size()) {
                merge(idx[i], i + 1);
                idx[i + 1] = idx[i];
            }
            else {
                merge(i + 1, idx[i]);
            }
        }
    }
    if (ok) {
        for (int i = 1; i <= n; i++) {
            std::cout << ans[i] << " \n"[i == n];
        }
    }
    else {
        std::cout << "-1\n";
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

/*
4
3 4
1 4
2 3
1 3

3 4 2 1
4 3 2 1
*/
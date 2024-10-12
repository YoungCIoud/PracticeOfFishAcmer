#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector<int> a(n + 1), in(n + 1);
    std::vector g(n + n + 1, std::vector<int>());
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        g[a[i]].push_back(i);
        if (a[i] <= n) {
            in[a[i]]++;
        }
    }

    std::queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    while (not q.empty()) {
        int cur = q.front();
        q.pop();

        int to = a[cur];
        if (to <= n) {
            in[to]--;
            if (in[to] == 0) {
                q.push(to);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (in[i] != 0) {
            ans++;
        }
    }

    auto dfs = [&](auto self, int cur) -> int {
        int res = 0;
        for (int &to : g[cur]) {
            res = std::max(res, self(self, to) + 1);
        }
        return res;
    };
    for (int i = 1; i <= n; i++) {
        ans += dfs(dfs, n + i);
    }
    
    std::cout << ans << '\n';
    return;
}

int main()
{
    //IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
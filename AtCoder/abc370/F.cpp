#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;

    vct<int> pre(n * 2 + 1);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> pre[i];
        pre[i + n] = pre[i];
        pre[i] += pre[i - 1];
    }
    for (int i = 1; i <= n; i++)
        pre[i + n] += pre[i + n - 1];

    std::vector<std::vector<int>> g(2 * n + 1);
    std::vector stk(2 * n, 0), f(2 * n, 0);
    auto chk = [&](int m)
    {
        g.assign(2 * n + 1, {});
        for (int i = 0, j = 1; i < 2 * n; i++)
        {
            while (j < 2 * n && pre[j] - pre[i] < m) j++;
            f[i] = j;
            g[j].push_back(i);
        }

        int ans = 0, p = 0;
        auto dfs = [&](auto self, int cur) -> void
        {
            if (cur < n && p >= k && stk[p - k] <= n + cur) ans++;
            stk[p++] = cur;
            for (int &to : g[cur])
                self(self, to);
            p--;
        };
        dfs(dfs, 2 * n);
        return ans;
    };

    int l = 1, r = pre[n] / k, ans = 0;
    while (l <= r)
    {
        int m = l + r >> 1;
        int res = chk(m);
        if (res == 0)
            r = m - 1;
        else
            l = m + 1, ans = n - res;
    }

    // chk(r);
    // for (int i = 1; i <= 2 * n; i++) std::cout << i << "\t\n"[i == 2 * n];
    // for (int i = 1; i <= 2 * n; i++) std::cout << f[i - 1] << "\t\n"[i == 2 * n];
    std::cout << r << ' ' << ans << '\n';
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
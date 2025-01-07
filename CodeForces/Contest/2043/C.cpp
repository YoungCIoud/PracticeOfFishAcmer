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
    std::vector a(n + 1, 0);
    int px = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        if (a[i] != 1 && a[i] != -1) {
            px = i;
        }
    }
    auto f = [&](int l, int r) -> std::pair<int, int> {
        int mx = 0, mn = 0;
        for (int i = l, u = 0, v = 0; i <= r; i++) {
            u = std::max(u + a[i], 0);
            v = std::min(v + a[i], 0);
            mx = std::max(mx, u);
            mn = std::min(mn, v);
        }
        return { mn, mx };
    };
    if (px) {
        std::vector<std::pair<int, int>> r;
        r.push_back(f(1, px - 1));
        r.push_back(f(px + 1, n));
        int mx = 0, mn = 0;
        r.push_back({ a[px], a[px] });
        for (int i = px - 1, sum = 0; i >= 1; i--) {
            sum += a[i];
            mx = std::max(mx, sum);
            mn = std::min(mn ,sum);
        }
        r[2].first += mn, r[2].second += mx;
        mx = 0, mn = 0;
        for (int i = px + 1, sum = 0; i <= n; i++) {
            sum += a[i];
            mx = std::max(mx, sum);
            mn = std::min(mn ,sum);
        }
        r[2].first += mn, r[2].second += mx;
        std::map<int, bool> vis;
        for (auto &[x, y] : r) {
            for (int i = x; i <= y; i++) {
                vis[i] = true;
            }
        }
        std::cout << vis.size() << '\n';
        for (auto &[x, y] : vis) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
    }
    else {
        auto ans = f(1, n);
        std::cout <<  ans.second - ans.first + 1 << '\n';
        for (int i = ans.first; i <= ans.second; i++) {
            std::cout << i << " \n"[i == ans.second];
        }
    }
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

    sp();

    return 0;
}
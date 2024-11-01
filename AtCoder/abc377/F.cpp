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
    int m = 0;
    std::cin >> n >> m;
    std::set<int> hor, ver, sla, bas;
    for (int i = 0; i < m; i++) {
        int x = 0, y = 0;
        std::cin >> x >> y;
        hor.emplace(x);
        ver.emplace(y);
        sla.emplace(x + y);
        bas.emplace(x - y);
    }

    i64 ans = 1ll * (n - hor.size()) * (n - ver.size());
    auto chk = [&](int x) -> bool {
        return 1 <= x && x <= n;
    };
    // x + y = d
    for (auto &d : sla) {
        std::set<int> crs;
        for (auto &x : hor) {
            if (chk(d - x)) {
                crs.emplace(x);
            }
        }
        for (auto &y : ver) {
            if (chk(d - y)) {
                crs.emplace(d - y);
            }
        }
        for (auto &e : bas) {
            if ((d + e) % 2 == 0 && chk((d + e) / 2) && chk((d - e) / 2)) {
                crs.emplace((d + e) >> 1);
            }
        }

        int l = n - abs(d - n - 1); 
        l -= crs.size();
        ans -= 1ll * l;
    }
    // x - y = d
    for (auto &d : bas) {
        std::set<int> crs;
        for (auto &x : hor) {
            if (chk(x - d)) {
                crs.emplace(x);
            }
        }
        for (auto &y : ver) {
            if (chk(y + d)) {
                crs.emplace(y + d);
            }
        }

        int l = n + (d > 0 ? -d : d);
        l -= crs.size();
        ans -= 1ll * l;
    }

    std::cout << ans << '\n';
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

    sp();

    return 0;
}
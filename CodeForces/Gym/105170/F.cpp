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
constexpr int N = 2e5, M = 2e5, Inf = 1e9;

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector py(n + 1, std::vector<int>{});
    std::vector con(m + 1, std::array<int, 5>{});
    std::multiset<int> s;
    for (int i = 1; i <= m; i++) {
        int a = 0, b = 0, x = 0, y = 0, z = 0;
        std::cin >> a >> b >> x >> y >> z;
        con[i] = { a, b, x, y, z };
        s.insert(std::max({ x, y, x + y + z + 1 >> 1 }));

        py[a].push_back(i);
        py[b].push_back(i);
    }

    std::vector<int> ans;
    for (int i = 1; i <= n; i++) {
        int sc = -1;
        std::vector<int> val;
        for (int j = 0; j < py[i].size(); j++) {
            auto &[a, b, x, y, z] = con[py[i][j]];
            int v = std::max({ x, y, x + y + z + 1 >> 1 });
            if (i == a) {
                if (x + z > y) {
                    sc = std::max(sc, x + z);
                    val.push_back(v);
                    s.erase(s.find(v));
                }
            }
            else {
                if (y + z > x) {
                    sc = std::max(sc, y + z);
                    val.push_back(v);
                    s.erase(s.find(v));
                }
            }
        }

        if (s.empty() || sc > *s.rbegin()) {
            ans.push_back(i);
        }

        for (auto v : val) {
            s.insert(v);
        }
    }

    std::cout << ans.size() << '\n';
    for (auto &i : ans) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
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
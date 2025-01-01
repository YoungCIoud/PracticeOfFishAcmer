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
constexpr int N = 200, M = 1e5, Inf = 1e9;

using pos = std::array<int, 2>;
using rang = std::array<int, 3>;

int n, m;
bool g[N + 5][N + 5], vis[N + 5];
int p[N + 5];

bool match(int cur) {
    for (int i = 0; i < m; i++) {
        if (!g[cur][i] || vis[i]) {
            continue;
        }

        vis[i] = true;
        if (p[i] == -1 || match(p[i])) {
            p[i] = cur;
            return true;
        }
    }
    return false;
}

void solve()
{
    std::cin >> n;
    std::vector<int> num;
    std::vector cas(n, pos{});
    for (auto &[x, y] : cas) {
        std::cin >> x >> y;
        num.push_back(x);
        num.push_back(y);
    }
    std::cin >> m;
    std::vector obs(m, pos{});
    for (auto &[x, y] : obs) {
        std::cin >> x >> y;
        num.push_back(x);
        num.push_back(y);
    }
    std::sort(num.begin(), num.end());
    num.erase(std::unique(num.begin(), num.end()), num.end());
    int l = num.size();
    std::vector row(l, std::set<std::pair<int, bool>>{});
    std::vector col(l, std::set<std::pair<int, bool>>{});
    for (auto &[x, y] : cas) {
        row[std::lower_bound(num.begin(), num.end(), x) - num.begin()].insert({ y, true });
        col[std::lower_bound(num.begin(), num.end(), y) - num.begin()].insert({ x, true });
    }
    for (auto &[x, y] : obs) {
        row[std::lower_bound(num.begin(), num.end(), x) - num.begin()].insert({ y, false });
        col[std::lower_bound(num.begin(), num.end(), y) - num.begin()].insert({ x, false });
    }

    std::vector<rang> hor; // 水平攻击的
    std::vector<rang> ver; // 竖直攻击的
    for (int i = 0; i < l; i++) {
        if (not row[i].empty()) {
            auto q = row[i].begin();
            auto p = q++;
            while (q != row[i].end()) {
                if ((*p).second && (*q).second) {
                    hor.push_back({ num[i], (*p).first, (*q).first });
                }
                p = q++;
            }
        }
        if (not col[i].empty()) {
            auto q = col[i].begin();
            auto p = q++;
            while (q != col[i].end()) {
                if ((*p).second && (*q).second) {
                    ver.push_back({ num[i], (*p).first, (*q).first });
                }
                p = q++;
            }
        }
    }
    n = hor.size(), m = ver.size();
    for (auto &[w, u, v] : hor) {
        if (u + 1 == v) {
            std::cout << -1 << '\n';
            return;
        }
    }
    for (auto &[w, u, v] : ver) {
        if (u + 1 == v) {
            std::cout << -1 << '\n';
            return;
        }
    }

    for (int i = 0; i < m; i++) {
        p[i] = -1;
        for (int j = 0; j < n; j++) {
            if (hor[j][1] < ver[i][0] && ver[i][0] < hor[j][2] && ver[i][1] < hor[j][0] && hor[j][0] < ver[i][2]) {
                g[j][i] = true;
            }
            else {
                g[j][i] = false;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        std::fill(vis, vis + m, false);
        match(i);
    }
    
    std::vector<pos> ans;
    for (int i = 0; i < m; i++) {
        if (~p[i]) {
            int x = hor[p[i]][0];
            int y = ver[i][0];
            row[std::lower_bound(num.begin(), num.end(), x) - num.begin()].insert({ y, false });
            col[std::lower_bound(num.begin(), num.end(), y) - num.begin()].insert({ x, false });
            ans.push_back({ x, y });
        }
    }

    for (int i = 0; i < l; i++) {
        if (not row[i].empty()) {
            auto q = row[i].begin();
            auto p = q++;
            while (q != row[i].end()) {
                if ((*p).second && (*q).second) {
                    ans.push_back({ num[i], (*p).first + 1 });
                }
                p = q++;
            }
        }
        if (not col[i].empty()) {
            auto q = col[i].begin();
            auto p = q++;
            while (q != col[i].end()) {
                if ((*p).second && (*q).second) {
                    ans.push_back({ (*p).first + 1, num[i] });
                }
                p = q++;
            }
        }
    }

    std::cout << ans.size() << '\n';
    for (auto &[u, v] : ans) {
        std::cout << u << ' ' << v << '\n';
    }
    return;
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
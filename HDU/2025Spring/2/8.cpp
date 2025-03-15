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
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 3e5, MAX = 1e4;

std::vector<int> g[N * 3 + 1];
int in[N * 3 + 1];

bool solve() {
    int n = 0, m = 0;
    std::cin >> n >> m;

    // init
    for (int i = 1; i <= 3 * n; i++) {
        in[i] = 0;
        g[i].clear();
    }

    bool ok = true;
    for (int i = 0; i < m; i++) {
        int x = 0, y = 0, col = 0;
        std::cin >> x >> y >> col;
        int c1 = y + 1 >> 1, c2 = 2 * n + 1 - x, c3 = (2 * x - y + 1 >> 1) + 2 * n;
       // std::cout << c1 << ' ' << c2 << ' ' << c3 << '\n';
        if (col != c1 && col != c2 && col != c3) {
            ok = false;
        }
        if (ok) {
            if (col != c1) {
                g[c1].push_back(col);
            }
            if (col != c2) {
                g[c2].push_back(col);
            }
            if (col != c3) {
                g[c3].push_back(col);
            }
        }
    }

    if (not ok) {
        return false;
    }
    
    for (int i = 1; i <= 3 * n; i++) {
        if (g[i].empty()) {
            continue;
        }

        std::sort(g[i].begin(), g[i].end());
        g[i].erase(std::unique(g[i].begin(), g[i].end()), g[i].end());
        for (int j = 0; j < int(g[i].size()); j++) {
            in[g[i][j]]++;
        }
    }

    std::queue<int> q;
    for (int i = 1; i <= 3 * n; i++) {
        if (in[i] == 0 && not g[i].empty()) {
            q.push(i);
        }
    }

    while (not q.empty()) {
        int cur = q.front();
        q.pop();

        for (auto &to : g[cur]) {
            if (--in[to] == 0) {
                q.push(to);
            }
        }
    }

    for (int i = 1; i <= 3 * n; i++) {
        if (in[i] != 0) {
            return false;
        }
    }

    return true;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        std::cout << (solve() ? "Yes" : "No" ) << '\n';
    }

    return 0;
}

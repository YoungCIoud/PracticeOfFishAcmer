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
constexpr int N = 100, Inf = 1e9;
typedef std::array<int, 2> point;

std::vector<std::array<point, 2>> ans;
std::vector<std::string> g;

// 0: 对齐行
// 1: 对齐列
point align(point u, point v, int id) {
    int d = u[id] > v[id] ? -1 : 1;
    while (u[id] != v[id]) {
        auto uu = u;
        uu[id] += d;
        std::swap(g[u[0]][u[1]], g[uu[0]][uu[1]]);
        ans.push_back({ u, uu });
        u = uu;
    }
    return u;
}

// u -> v;
void move(point u, point v, int fir, int sec) {
    align(align(u, v, fir), v, sec);
    return;
}

void solve()
{
    ans.clear();

    int n = 0;
    std::cin >> n;
    g.assign(n, {});
    for (auto &s : g) {
        std::cin >> s;
    }
    
    for (int i = 0; i + i < n; i++) {
        for (int j = 0; j + j < n; j++) {
            if (g[i][j] == '1') {
                continue;
            }

            bool find = false;
            for (int y = j; y < n && not find; y++) {
                for (int x = (y + y < n ? i : 0); x < n && not find; x++) {
                    if (g[x][y] == '1') {
                        find = true;
                        move({ x, y }, { i, j }, 0, 1);
                    }
                }
            }

            for (int x = i + 1; x < n && not find; x++) {
                for (int y = j - 1; ~y && not find; y--) {
                    if (g[x][y] == '1') {
                        find = true;
                        move({ x, y }, { i, j }, 1, 0);
                    }
                }
            }
            // for (auto &s : g) {
            //     std::cout << s << '\n';
            // }
        }
    }

    std::cout << ans.size() << '\n';
    for (auto &[u, v] : ans) {
        std::cout << u[0] + 1 << ' ' << u[1] + 1 << ' ';
        std::cout << v[0] + 1 << ' ' << v[1] + 1 << '\n';
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
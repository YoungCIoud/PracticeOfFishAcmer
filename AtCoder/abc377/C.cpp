#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#ifdef LOCAL_MACHINE
	#define debug(...) printf(__VA_ARGS__)
	#define sp() system("pause")
#else
	#define debug(...)
	#define sp()
#endif
using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;
int n, m;
std::set<std::pair<int, int>> mp;

void insert(std::pair<int, int> a) {
    if (mp.count(a) == 0) {
        mp.insert(a);
    }
}

bool chk(std::pair<int, int> a) {
    auto [x, y] = a;
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

std::vector<std::pair<int, int>> find(std::pair<int, int> a) {
    std::vector<std::pair<int, int>> res;
    if (chk(a)) {
        res.push_back(a);
    }
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                int x = a.first + (k ? 2 : 1) * ((i == 0) ? -1 : 1);
                int y = a.second + (k ? 1 : 2) * ((j == 0) ? -1 : 1);
                if (chk({ x, y })) {
                    res.push_back({ x, y });
                }
            }
        }
    }
    return res;
}

void solve()
{
    std::cin >> n >> m;
    while (m--) {
        int x = 0, y = 0;
        std::cin >> x >> y;
        for (auto &p : find({ x, y })) {
            insert(p);
        }
    }
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         std::cout << mp.count({ i, j }) << "\000\n"[j == n];
    //     }
    // }
    std::cout << 1ll * n * n - 1ll * mp.size() << '\n';
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
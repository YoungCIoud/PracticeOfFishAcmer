#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;
int n = 0, q = 0;

std::vector<std::pair<int, int>> trans(int from, int to, int mid) {
    std::vector<std::pair<int, int>> res;
    if (to == from) {
        res.push_back({ mid, 0 });
        return res;
    }
    if (mid != to) {
        if (mid < std::min(from, to) || std::max(from, to) < mid) {
            res.push_back({ mid, (abs(from - to)) });
        }
        else {
            res.push_back({ mid, n - abs(from - to) });
        }
    }

    int v1 = (n + to - mid) % n + 1 + (n + to - from) % n;
    int v2 = (n + mid - to) % n + 1 + (n + from - to) % n;
    if (from < mid) {
        // 顺时针
        if (to < from || mid <= to) {
            res.push_back({ (to + 1) % n, v1 });
        }
        // 逆时针
        if (from < to && to <= mid) {
            res.push_back({ to - 1, v2 });
        }
    }
    else {
        // 顺时针
        if (mid <= to && to < from) {
            res.push_back({ to + 1, v1 });
        }
        // 逆时针
        if (to <= mid || from < to) {
            res.push_back({ (n + to - 1) % n, v2 });
        }
    }

    return res;
}

void solve()
{
    std::cin >> n >> q;

    int lstc = 0, lstp = 0;
    std::vector f(2, std::vector(n, Inf));
    f[0][1] = 0;
    for (int i = 1; i <= q; i++) {
        int u = i & 1, v = u ^ 1;
        for (int j = 0; j < n; j++) {
            f[u][j] = Inf;
        }
        char ch = 0;
        int curc = 0, curp = 0;
        std::cin >> ch >> curp;
        curp--;
        if (ch == 'R') {
            curc = 1;
        }

        std::array<int, 2> lst{};
        for (int j = 0; j < n; j++) {
            if (f[v][j] == Inf || lstp == j) {
                continue;
            }
            lst[lstc] = lstp;
            lst[lstc ^ 1] = j;
            for (auto [pos, val] : trans(lst[curc], curp, lst[curc ^ 1])) {
                f[u][pos] = std::min(f[u][pos], f[v][j] + val);
            }
        }
        lstc = curc, lstp = curp;
    }

    int ans = Inf;
    for (int i = 0; i < n; i++) {
        ans = std::min(ans, f[q & 1][i]);
    }
    std::cout << ans << '\n';
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

    system("pause");

    return 0;
}
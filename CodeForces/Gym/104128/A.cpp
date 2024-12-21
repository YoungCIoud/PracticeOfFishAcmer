#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

typedef std::array<int, 2> Node;
int dx['Z'], dy['Z'];
char inv['Z'];

void solve()
{
    int n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;
    std::string s{};
    std::cin >> s;
    Node A = { 0, 0 }, B = { n, m };

    auto chk = [&](Node& p, char c, int l = 0) -> bool {
        int x = p[0] + dx[c], y = p[1] + dy[c];
        if (l <= x && x <= n && l <= y && y <= m) {
            p = { x, y };
            return true;
        }
        else {
            return false;
        }
    };
    
    int totdx = 0, totdy = 0;
    for (auto &c : s) {
        totdx += dx[c];
        totdy += dy[c];
        chk(A, c);
        chk(B, c);
    }
    A[0] -= totdx, A[1] -= totdy;
    B[0] -= totdx, B[1] -= totdy;
    int h = B[0] - A[0], w = B[1] - A[1];

    if (h * w < k) {
        std::cout << 0 << '\n';
        return;
    }
    if (h * w == 0 && k == 0) {
        std::cout << n * m << '\n';
        return;
    }

    // the height of trace < n ans the width of trace < m
    std::vector trace(2 * n + 2, std::vector(2 * m + 2, 0));
    int curx = n, cury = m;
    Node mn = { n, m };
    trace[n][m] = 1;
    for (auto &c : s) {
        curx += dx[inv[c]];
        cury += dy[inv[c]];
        mn[0] = std::min(mn[0], curx);
        mn[1] = std::min(mn[1], cury);
        trace[curx][cury] = 1;
    }
    Node cen = { n - mn[0] + 1, m - mn[1] + 1 };

    std::vector pre(n + 1, std::vector(m + 1, 0));
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + trace[i + mn[0] - 1][j + mn[1] - 1];
            Node t = { B[0] + cen[0] - i, B[1] + cen[1] - j };
            if (chk( t, 0, 1 )) {
                int u = std::max(0, i - h);
                int v = std::max(0, j - w);
                int fall = pre[i][j] - pre[u][j] - pre[i][v] + pre[u][v];
                if (h * w - fall == k) {
                    ans++;
                }
            }
        }
    }
    std::cout << ans << '\n';
    return;
}

int main()
{
    dx['U'] = -1, dy['U'] = 0, inv['U'] = 'D';
    dx['D'] = 1, dy['D'] = 0, inv['D'] = 'U';
    dx['L'] = 0, dy['L'] = -1, inv['L'] = 'R';
    dx['R'] = 0, dy['R'] = 1, inv['R'] = 'L';

    // IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
// int g[10][10];
// bool chk(int x1, int y1, int x2, int y2) {
//     if (g[x1][y1] == g[x1][y2] && g[x2][y1] == g[x2][y2]) {
//         return true;
//     }
//     if (g[x1][y1] == g[x2][y1] && g[x1][y2] == g[x2][y2]) {
//         return true;
//     }
//     return false;
// }
// i64 dfs(int n, int m, int cur = 0) {
//     if (cur >= n * m) {
//         return 1;
//     }
//     int x = cur / m, y = cur % m;
//     i64 val = 0;
//     for (int c = 0; c < 3; c++) {
//         bool flag = true;
//         g[x][y] = c;
//         for (int tx = 0; tx < x && flag; tx++) {
//             for (int ty = 0; ty < y && flag; ty++) {
//                 if (chk(x, y, tx, ty)) {
//                     flag = false;
//                 }
//             }
//         }
//         if (flag) {
//             (val += dfs(n, m, cur + 1)) %= Mod;
//         }
//     }
//     return val;
// }
// void init() {
//     for (int i = 2; i <= 9; i++) {
//         for (int j = i; j <= 9; j++) {
//             ans[i][j] = (qpow(3, i * j) - dfs(i, j) + Mod) % Mod;
//         }
//     }
//     // debug("init ok\n");
//     std::array<std::string, 2> s;
//     s[0] = ", ";
//     s[1] = "\n";
//     for (int i = 1; i <= 9; i++) {
//         for (int j = 1; j <= 9; j++) {
//             std::cout << ans[i][j] << s[j == 9];
//         }
//     }
// }

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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;
i64 ans[10][10] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 15, 339, 4761, 52929, 517761, 4767849, 43046721, 387420489,
    0, 0, 0, 16485, 518265, 14321907, 387406809, 460338013, 429534507, 597431612,
    0, 0, 0, 0, 43022385, 486780060, 429534507, 792294829, 175880701, 246336683,
    0, 0, 0, 0, 0, 288599194, 130653412, 748778899, 953271190, 644897553,
    0, 0, 0, 0, 0, 0, 246336683, 579440654, 412233812, 518446848,
    0, 0, 0, 0, 0, 0, 0, 236701429, 666021604, 589237756,
    0, 0, 0, 0, 0, 0, 0, 0, 767713261, 966670169,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 968803245
};

i64 qpow(i64 a, int p) {
    i64 res = 1;
    for (; p; p >>= 1, a = a * a % Mod) {
        if (p & 1) {
            res = a * res % Mod;
        }
    }
    return res % Mod;
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    
    if (n > m) {
        std::swap(n, m);
    }
    if (n == 1) {
        std::cout << 0 << '\n';
    }
    else if (m > 9) {
        std::cout << qpow(3, n * m) << '\n';
    }
    else {
        std::cout << ans[n][m] << '\n';
    }
}

int main()
{
    // init();

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
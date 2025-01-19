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

// void solve()
// {
//     int n = 0;
//     std::cin >> n;
//     std::vector g(n + 1, std::string{});
//     for (int i = 1; i <= n; i++) {
//         std::cin >> g[i];
//     }
//     std::vector p(n + 1, 0);
//     for (int i = 1; i <= n; i++) {
//         int cnt = 0;
//         for (int j = i; j < n; j++) {
//             if (g[i][j] == '1') {
//                 cnt++;
//             }
//         }
//         for (int j = n; j >= 1; j--) {
//             if (p[j] == 0) {
//                 if (cnt == 0) {
//                     p[j] = i;
//                     break;
//                 }
//                 else {
//                     cnt--;
//                 }
//             }
//         }
//     }
//     for (int i = 1; i <= n; i++) {
//         std::cout << p[i] << " \n"[i == n];
//     }
//     return;
// }

void solve() {
    int n = 0;
    std::cin >> n;
    std::vector g(n, std::string{});
    for (auto &s : g) {
        std::cin >> s;
    }
    std::vector p(n, 0);
    std::iota(p.begin(), p.end(), 0);

    std::sort(p.begin(), p.end(), [&](int x, int y) {
        return (g[x][y] == '1' ? (x < y) : (x > y));
    });

    for (auto &i : p) {
        std::cout << i + 1 << ' ';
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
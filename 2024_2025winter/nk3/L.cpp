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
constexpr int N = 50, M = 1e5, Inf = 1e9;
void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector idx(n + 1, std::vector<int>{});
    for (int i = 0, m = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            // std::cout << m << '\t';
            idx[i].push_back(m++);
        }
        // std::cout << '\n';
    }
    
    std::cout << "Yes\n";
    for (int i = 0; i + 1 < n; i++) {
        std::cout << idx[i][0] << ' ';
    }
    for (int j = 0; j < n; j++) {
        std::cout << idx[n - 1][j] << ' ' << idx[n][j] << ' ' << idx[n][j + 1] << ' ' << idx[n - 1][j] << ' ';
    }
    for (int i = n - 2; i >= 0; i--) {
        std::cout << idx[i].back() << ' ';
        for (int j = i - 1; j >= 0; j--) {
            std::cout << idx[i + 1][j + 1] << ' ' << idx[i][j] << ' ';
        }
        for (int j = 1; j <= i; j++) {
            std::cout << idx[i][j] << ' ';
        }
    }
    std::cout << '\n';
    return;
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
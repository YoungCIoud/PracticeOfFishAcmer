#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), \
                std::cin.tie(0), \
                std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int Q = 5e5, X = 5e5, Y = 1e3, L = 710; // sqrt(Q)

int a[X + 5];
int ans[L][L];

void solve()
{
    int q = 0;
    std::cin >> q;
    while (q--) {
        int op = 0, x = 0, y = 0;
        std::cin >> op >> x >> y;
        if (op == 1) {
            a[x] += y;
            for (int i = 1; i < L; i++) {
                ans[i][x % i] += y;
            }
        }
        else {
            int sum = 0;
            if (x < L) {
                sum = ans[x][y];
            }
            else {
                for (int i = y; i <= X; i += x) {
                    sum += a[i];
                }
            }
            std::cout << sum << '\n';
        }
    }
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
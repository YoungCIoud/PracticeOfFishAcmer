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
constexpr int N = 1e4;
double mul[N + 5];
i64 sub[N + 5];

void solve()
{
    int p = 0, n = 0, k = 0;
    std::cin >> p >> n >> k;
    for (int i = 0; i <= n; i++) {
        mul[i] = 1.0,
        sub[i] = 0;
    }
    int c0 = 0, c1 = 0;
    for (int i = 0; i < n; i++) {
        int op = 0, x = 0;
        std::cin >> op >> x;
        if (op == 0) {
            mul[++c0] = 1.0 * x / 10.0;
        }
        else {
            sub[++c1] = x;
        }
    }
    std::sort(mul + 1, mul + 1 + n);
    std::sort(sub + 1, sub + 1 + n, std::greater<i64>());
    for (int i = 1; i <= n; i++) {
        mul[i] *= mul[i - 1];
        sub[i] += sub[i - 1];
    }

    double ans = p;
    for (int i = 0; i <= k; i++) {
        ans = std::min(ans, 1.0 * mul[i] * p - sub[k - i]);
    }
    if (ans < 0.0) {
        ans = 0;
    }
    std::cout << std::fixed << std::setprecision(2) << ans << '\n';
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

/*
3
79 4 2
0 9
1 14
0 5
0 8
71 4 3
1 22
1 3
0 6
0 7
70 5 3
1 18
0 2
0 1
0 9
1 7
*/
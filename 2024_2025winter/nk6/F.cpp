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

class cmp {
public:
    bool operator()(std::array<int, 2> u, std::array<int, 2> v) {
        return u[0] > v[0];
    }
};

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n, std::array<int, 2>{ 0, 0 });
    for (auto &[x, y] : a) {
        std::cin >> x >> y;
    }
    std::sort(a.begin(), a.end(), [&](auto &u, auto &v) {
        if (u[0] + u[1] == v[0] + v[1]) {
            return u[0] < v[0];
        }
        else {
            return u[0] + u[1] < v[0] + v[1];
        }
    });

    int mx = a[0][0];
    for (int i = 1; i < n; i++) {
        if (mx >= a[i][0]) {
            mx = std::max(mx, a[i][0] + a[i][1]);
        }
        else {
            mx = std::max(mx, a[i][0]);
            mx = std::max(mx, a[i - 1][0] + a[i - 1][1]);
        }
    }

    std::cout << mx << '\n';
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
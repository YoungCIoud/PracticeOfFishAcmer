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

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n, std::array<int, 2>{});
    for (int i = 0; i < n; i++) {
        std::cin >> a[i][0] >> a[i][1];
        a[i][0] -= i, a[i][1] = i - a[i][1];
    }
    std::sort(a.begin(), a.end(), [](auto &u, auto &v) { return u[0] != v[0] ? u[0] < v[0] : u[1] < v[1]; });
    
    std::stack<int> stk;
    for (auto &[A, B] : a) {
        if (stk.empty() || B < stk.top()) {
            stk.push(B);
        }
        else {
            int mn = stk.top();
            while (not stk.empty() && B >= stk.top()) {
                stk.pop();
            }
            stk.push(mn);
        }
    }

    std::cout << stk.size() << '\n';
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
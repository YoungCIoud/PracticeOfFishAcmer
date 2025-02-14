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
    int n = 0, x = 0, y = 0;
    std::cin >> n >> x >> y;
    int ans = 0;
    // 枚举前面只磨刀的轮数
    for (int i = 0; i <= std::min(n, y); i++) {
        int d0 = x + i; // 初始伤害
        int con = std::min(n, y) - i; // 边磨刀边攻击的轮数
        int att = std::min(n - con - i, d0); // 只攻击的轮数
        ans = std::max(ans, (d0 + 1) * con + (2 * d0 - att + 1) * att / 2);
    }
    std::cout << ans << '\n';
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

/*
3
2 1 1
5 1 3
5 1 5
3
9
12
*/
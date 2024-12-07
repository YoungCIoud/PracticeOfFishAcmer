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

bool solve()
{
    int n = 0;
    std::cin >> n;
    std::array<i64, 2> s{ 0, 0 };
    for (int i = 1; i <= n; i++) {
        int a = 0;
        std::cin >> a;
        s[i & 1] += a;
    }
    int n0 = n / 2, n1 = n - n0;
    return (s[0] % n0 == 0 && s[1] % n1 == 0) && (s[0] / n0 == s[1] / n1);
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        std::cout << (solve() ? "Yes" : "No") << '\n';
    }

    sp();

    return 0;
}
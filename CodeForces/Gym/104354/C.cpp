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
    std::string s;
    std::cin >> s;
    int L = 1e3, R = 1e4;
    for (int i = L; i <= R; i++) {
        if (s.substr(0, L) == s.substr(i, L)) {
            return false;
        }
    }
    return true;
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        std::cout << (solve() ? "Yes" : "No") << '\n';
    }

    sp();

    return 0;
}
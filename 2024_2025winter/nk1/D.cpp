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
    std::map<int, int> m;
    for (int i = 1; i <= n; i++) {
        int x = 0;
        std::cin >> x;
        m[x]++;
    }
    if (m.size() != 2) {
        return false;
    }
    else {
        std::vector<int> a;
        for (auto &[ x, y ] : m) {
            a.push_back(y);
        }
        return a[0] == a[1];
    }
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        puts(solve() ? "Yes" : "No");
    }

    sp();

    return 0;
}
#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    #define cout cout << ">>>\t"
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
    std::vector p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> p[i];
    }

    for (int i = 1; i < n; i++) {
        if (p[i] != i) {
            if (p[i] == i + 1 && p[i + 1] == i) {
                i++;
            }
            else {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        std::cout << (solve() ? "Yes" : "No") << '\n';
    }

    sp();

    return 0;
}
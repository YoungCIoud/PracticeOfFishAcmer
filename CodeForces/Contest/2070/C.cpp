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
    int n = 0, k = 0;
    std::string s;
    std::cin >> n >> k >> s;
    std::vector p(n, 0);
    for (auto &i : p) {
        std::cin >> i;
    }
    
    int l = 0, r = 1e9;
    while (l <= r) {
        int m = l + r >> 1;
        
        int cnt = 0;
        bool paint = false;
        for (int i = 0; i < n; i++) {
            if (p[i] > m) {
                if (s[i] == 'R') {
                    paint = false;
                }
                else if (!paint){
                    paint = true;
                    cnt++;
                }
            }
        }

        if (cnt <= k) {
            r = m - 1;
        }
        else {
            l = m + 1;
        }
    }
    std::cout << l << '\n';
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
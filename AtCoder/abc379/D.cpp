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

void solve()
{
    int Q = 0;
    std::cin >> Q;
    std::priority_queue<i64> q;
    i64 tim = 0;
    while (Q--) {
        int ope = 0;
        std::cin >> ope;
        if (ope == 1) {
            q.push(-tim);
        }
        else if (ope == 2) {
            int T = 0;
            std::cin >> T;
            tim += T;
        }
        else {
            int H = 0;
            std::cin >> H;
            int ans = 0;
            while (not q.empty() && q.top() + tim >= H) {
                q.pop();
                ans++;
            }
            std::cout << ans << '\n';
        }
    }
    return;
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
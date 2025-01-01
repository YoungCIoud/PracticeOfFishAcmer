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
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector s(n, std::pair<int, int>{});
    for (auto &[l, r] : s) {
        std::cin >> l >> r;
    }
    std::sort(s.begin(), s.end());
    
    std::priority_queue<int> mn, mx;
    i64 ans = 1;
    for (auto &[l, r] : s) {
        while (not mx.empty() && mx.top() >= l) {
            mn.push(-mx.top());
            mx.pop();
        }
        while (not mn.empty() && -mn.top() < l) {
            mx.push(-mn.top());
            mn.pop();
        }
        (ans *= k - mn.size()) %= Mod;
        if (ans == 0) {
            break;
        }

        mn.push(-r);
        if (not mx.empty()) {
            mx.pop();
        }
    }
    std::cout << ans << '\n';
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
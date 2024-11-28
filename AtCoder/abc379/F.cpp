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
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::vector h(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> h[i];
    }

    std::vector quiry(q, std::array<int, 3>{});
    for (int i = 0; i < q; i++) {
        std::cin >> quiry[i][1] >> quiry[i][2];
        quiry[i][0] = i;
    }
    std::sort(quiry.begin(), quiry.end(), [&](std::array<int, 3> &x, std::array<int, 3> &y){
        return x[1] > y[1];
    });

    std::vector stk(n, 0), ans(q, 0);
    int top = 0, lst = n;
    for (auto &[id, l, r] : quiry) {
        for (lst; lst > l; lst--) {
            while (top != 0 && h[stk[top - 1]] < h[lst]) {
                top--;
            }
            stk[top++] = lst;
        }
        ans[id] = std::lower_bound(stk.begin(), stk.begin() + top, r, std::greater()) - stk.begin();
    }
    for (auto &i : ans) {
        std::cout << i << '\n';
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
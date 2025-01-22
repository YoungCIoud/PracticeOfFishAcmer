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
constexpr int Q = 3e5, M = 1e5, Inf = 1e9;

void solve()
{
    int q = 0;
    std::cin >> q;
    std::array<i64, 2> sum = { 0, 0 };
    std::vector<std::pair<int, i64>> s;
    while (q--) {
        int ope = 0;
        std::cin >> ope;
        if (ope == 1) {
            i64 l = 0;
            std::cin >> l;
            s.push_back({ l, (s.empty() ? 0 : s.back().second) + l});
        }
        else if (ope == 2) {
            sum[1] += s[sum[0]++].first;
        }
        else {
            int k = 0;
            std::cin >> k;
            int id = k - 1 + sum[0];
            std::cout << s[id].second - s[id].first - sum[1] << '\n';
        }
    }
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
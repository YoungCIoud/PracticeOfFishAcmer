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
constexpr int N = 1e5, M = 1e9, Inf = 1e9 + 10;

void solve()
{
    // 怪物数量 最大伤害 最终需要消灭的怪物的数量 
    int n = 0, m = 0, k = 0;
    std::cin >> n >> m >> k;
    std::vector<int> h(n, 0), p(n, 0);
    for (auto &i : h) {
        std::cin >> i;
    }
    for (auto &i : p) {
        std::cin >> i;
    }
    auto chk = [&](int t) -> bool {
        std::map<int, int> cnt;
        for (int i = 0; i < n; i++) {
            int d = m - ceil(1.0 * h[i] / t);
            if (d >= 0) {
                cnt[std::max(p[i] - d, p.front())]++;
                cnt[std::min(p[i] + d + 1, p.back() + 1)]--;
            }
        }
        int kk = 0;
        for (auto& [pos, val] : cnt) {
            kk += val;
            if (kk >= k) {
                return true;
            }
        }
        return false;
    };
    int l = 1, r = Inf;
    while (l <= r) {
        int mid = l + r >> 1;
        if (chk(mid)) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    std::cout << (l > Inf ? -1 : l) << '\n';
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
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
constexpr int N = 12e5, M = 1e6, Inf = 1e9;
int cnt[M + 1]; // cnt[i] 表示 i 的倍数有多少个
int ans[M + 1];

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    int mx = 0;
    std::vector a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
        cnt[i]++;
        mx = std::max(mx, i);
    }
    for (int i = 1; i <= mx; i++) {
        for (int j = i + i; j <= mx; j += i) {
            cnt[i] += cnt[j];
        }
    }

    for (int i = 1; i <= mx; i++) {
        if (cnt[i] < k) {
            continue;
        }
        for (int j = i; j <= mx; j += i) {
            ans[j] = i;
        }
    }
    for (auto &i : a) {
        std::cout << ans[i] << '\n';
    }
    return;
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
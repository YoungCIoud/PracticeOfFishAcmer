#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 4e6, D = 2e6;
int tot[N + 5], cnt[N + 5], LM[N + 5];

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    
    std::vector a(n, 0);
    int mx = 0;
    for (auto &i : a) {
        std::cin >> i;
        i += D;
        tot[i]++;
        mx = std::max(mx, tot[i]);
    }
    if (k == 0) {
        std::cout << mx << '\n';
        return;
    }

    int ans = 0;
    // 枚举区间右端点
    for (int i = 0; i < n; i++) {
        int R = tot[a[i] + k] - cnt[a[i] + k];
        LM[a[i]] = std::max(LM[a[i]], cnt[a[i] + k] - cnt[a[i]]);
        cnt[a[i]]++;
        ans = std::max(ans, LM[a[i]] + R + cnt[a[i]]);
    }

    std::cout << ans << '\n';
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
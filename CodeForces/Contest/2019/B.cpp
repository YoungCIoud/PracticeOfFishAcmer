#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::map<i64, i64> cnt;

    std::vector<int> p(n + 1);
    std::cin >> p[1];
    cnt[1 * n - 1]++;

    for (int i = 2; i <= n; i++) {
        std::cin >> p[i];
        cnt[1ll * i * (n - i + 1) - 1]++;
        cnt[1ll * (i - 1) * (n - i + 1)] += p[i] - p[i - 1] - 1;
    }

    while (q--) {
        i64 k = 0;
        std::cin >> k;
        std::cout << cnt[k] << ' ';
    }
    std::cout << '\n';
    return;
;}

int main()
{
    // IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
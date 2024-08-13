#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

// 使到三个源点距离的最小值最大
void solve()
{
    int n;
    str a, b, c;
    std::cin >> n >> a >> b >> c;

    int ans = 0;
    ary<int, 3> cnt{};
    for (int i = 0; i < n; i++)
    {
        if (a[i] == b[i] && b[i] == c[i]) ans++;
        else if (b[i] == c[i] && a[i] != b[i]) cnt[0]++;
        else if (a[i] == c[i] && b[i] != a[i]) cnt[1]++;
        else cnt[2]++;
    }
    std::sort(cnt.begin(), cnt.end());
    ans += cnt[0] * 2;
    cnt[1] -= cnt[0], cnt[2] -= cnt[0];
    
    ans += cnt[1];
    cnt[2] -= cnt[1];

    ans += cnt[2] / 2;
    std::cout << ans << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
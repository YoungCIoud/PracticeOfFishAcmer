#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e9;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    vct<int> a(n + 2);
    // 最大的非正数和最小的非负数
    int L = 0, R = n + 1;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
    }
    a[0] = -Inf, a[n + 1] = Inf;
    while (a[L] <= 0) L++; L--;
    while (a[R] >= 0) R--; R++;

    int ans = 0;

    // 一直向右
    for (int r = n; r >= R; r--)
    {
        if (a[r] <= n - r)
        {
            ans = r - R + 1;
            break;
        }
    }
    // 一直向左
    for (int l = 1; l <= L; l++)
    {
        if (-a[l] <= l - 1)
        {
            ans = std::max(ans, L - l + 1);
            break;
        }
    }
    // 右拐左
    for (int r = n, l = L; r >= R && l >= 1; r--)
    {
        if (a[r] > n - r) continue;

        while (a[r] - a[l] <= l - 1) l--;
        ans = std::max(ans, r - l);
    }
    // 左拐右
    for (int l = 1, r = R; l <= L && r <= n; l++)
    {
        if (-a[l] > l - 1) continue;

        while (a[r] - a[l] <= n - r) r++;
        ans = std::max(ans, r - l);
    }

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
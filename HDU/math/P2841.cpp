#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;
int pr[10], num;

// 返回[1,n]内有多少个数同m互质
i64 cnt(int n, int m)
{
    num = 0;
    for (int i = 2; i * i <= m; i++)
    {
        if (m % i) continue;
        while (m % i == 0) m /= i;
        pr[num++] = i;
    }
    if (m != 1) pr[num++] = m;

    i64 res = 0;
    for (int i = 1; i < (1 << num); i++)
    {
        int p = 1, cnt = 0;
        for (int j = 0; j < num; j++)
            if ((i >> j) & 1) p *= pr[j], cnt++;
        if (cnt & 1) res += n / p;
        else res -= n / p;
    }

    return n - res;
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    if (n > m) std::swap(n, m);

    i64 ans = 0;
    for (int i = 1; i <= n; i++)
        ans += cnt(m, i);
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
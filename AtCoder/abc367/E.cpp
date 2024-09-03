#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 2e5, M = 1e5;

void solve()
{
    int n = 0;
    i64 k = 0;
    std::cin >> n >> k;
    vct st(n + 1, vct<int>(64, 0));
    vct a(n + 1, 0);
    for (int i = 1; i <= n; i++) std::cin >> st[i][0];
    for (int i = 1; i <= n; i++) std::cin >> a[i];

    for (int l = 1; l < 64; l++)
        for (int i = 1; i <= n; i++)
            st[i][l] = st[st[i][l - 1]][l - 1];

    vct<int> d{};
    for (int i = 0; i < 64; i++, k >>= 1)
        if (k & 1) d.push_back(i);

    for (int i = 1; i <= n; i++)
    {
        int cur = i;
        for (auto &nex : d)
            cur = st[cur][nex];
        std::cout << a[cur] << " ";
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

    // system("pause");

    return 0;
}
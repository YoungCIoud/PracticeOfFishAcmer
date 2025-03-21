#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::map<str, int> cnt{};

    for (int i = 1; i <= n; i++)
    {
        str s{};
        std::cin >> s;
        cnt[s]++; 
    }

    int mx = 0;
    for (auto &[s, num] : cnt)
        mx = std::max(mx, num);
    
    str ans{};
    for (auto &[s, num] : cnt)
        if (num == mx) ans = s;

    if (mx + mx > n) std::cout << ans << '\n';
    else std::cout << "uh-oh" << '\n';
    return;
}

int main()
{
    //IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
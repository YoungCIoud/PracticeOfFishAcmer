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
    vct<int> a(n);
    for (auto &i : a) std::cin >> i;
    if (a[0] > a[1]) std::swap(a[0], a[1]);
    if (n == 2 && a[1] - a[0] != 1) std::cout << "Yes" << '\n';
    else std::cout << "No" << '\n';
    return;
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
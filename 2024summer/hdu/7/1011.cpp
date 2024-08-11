#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    i64 a = 0, b = 0;
    std::cin >> a >> b;

    if (a % b == 0)
    {
        std::cout << b << " " << a / b << '\n';
        return;
    }

    a *= 2ll;
    std::cout << b << " " << a / std::__gcd(a ,b) << '\n';
}

int main()
{
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
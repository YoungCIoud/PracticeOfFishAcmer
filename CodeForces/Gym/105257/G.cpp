#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    std::string s;
    int x;
    std::cin >> s >> x;
    for (auto &c : s) {
        if (c - '0' > x) {
            c--;
        }
    }

    i64 n = std::stoll(s);
    i64 ans = 1;
    i64 p = 1;
    while (n) {
        ans += (n % 10ll) * p;
        n /= 10ll;
        p *= 9ll;
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
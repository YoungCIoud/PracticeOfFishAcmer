#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    i64 b = 0, c = 0, d = 0;
    std::cin >> b >> c >> d;
    i64 aim = d - (b - c);
    if (aim < 0) {
        puts("-1");
        return;
    }

    i64 a = 0;
    for (int i = 61; i >= 0; i--, a <<= 1) {
        int x = b >> i & 1, y = c >> i & 1;
        if ((1ll << i) <= aim) {
            if (x == 1 && y == 0) {
                puts("-1");
                return;
            }
            if (x == 0 && y == 0) {
                a |= 1;
            }

            aim -= (1ll << i);
        }
        else {
            if (x == 1 && y == 1) {
                a |= 1;
            }
            else if (x == 0 && y == 1) {
                puts("-1");
                return;
            }
        }
    }

    std::cout << (aim ? -1 : (a >> 1)) << '\n';
    return;
}

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
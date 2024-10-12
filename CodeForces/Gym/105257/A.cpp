#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    std::string s, h = "xwr";
    std::cin >> s;
    
    for (char &c : s) {
        int a = c - '0';
        for (int i = 2; i >= 0; i--) {
            if ((a >> i) & 1) {
                std::cout << h[i];
            }
            else {
                std::cout << '-';
            }
        }
    }
    std::cout << '\n';
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
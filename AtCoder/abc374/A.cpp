#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

bool solve()
{
    std::string s;
    std::cin >> s;
    int n = s.length();
    return s[n - 1] == 'n' && s[n - 2] == 'a' && s[n - 3] == 's';
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        puts(solve() ? "Yes" : "No");
    }

    system("pause");

    return 0;
}
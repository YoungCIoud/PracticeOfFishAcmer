#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

int solve()
{
    std::string s, t;
    std::cin >> s >> t;
    if (s == t) {
        return 0;
    }
    if (s.length() > t.length()) std::swap(s, t);
    
    int ans = s.length();
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != t[i]) {
            ans = i;
            break;
        }
    }
    return ans + 1;
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        std::cout << solve() << '\n';
    }

    system("pause");

    return 0;
}
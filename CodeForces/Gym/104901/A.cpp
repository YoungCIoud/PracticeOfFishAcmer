#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

bool solve()
{
    str s;
    std::cin >> s;
    for (auto &c : s)
        if (c == ')') c = '(';
        else if (c == ']') c = '[';
    int cnt = 0;
    for (int i = 1; i < s.size(); i++)
        if (s[i] == s[i - 1]) cnt++;
    
    return cnt > 2;
}

int main()
{
    //IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
        std::cout << (solve() ? "No" : "Yes") << '\n'; 

    system("pause");

    return 0;
}
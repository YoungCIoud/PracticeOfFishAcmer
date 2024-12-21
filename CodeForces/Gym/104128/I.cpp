#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    std::string s;
    std::cin >> s;
    std::vector cnt(26, 0);
    for (auto &c : s) {
        cnt[c - 'a']++;
    }
    int mx = 0;
    for (auto &i : cnt) {
        mx = std::max(mx ,i);
    }
    std::cout << s.size() - mx << '\n';
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
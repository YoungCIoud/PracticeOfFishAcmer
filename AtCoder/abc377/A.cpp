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
    bool cnt[3] = { false, false, false };
    for (int i = 0; i < 3; i++) {
        if (s[i] > 'C' || cnt[s[i] - 'A']) {
            puts("No");
            return;
        }
        cnt[s[i] - 'A'] = true;
    }
    puts("Yes");
    return;
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
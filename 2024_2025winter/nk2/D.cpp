#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

int solve(int n, std::string s)
{
    s = "#" + s;

    std::vector cnt(26, 0);
    int ans = 0;
    for (int i = n; i >= 1; i--) {
        int m = cnt[s[i] - 'a']++;
        if (m) {
            ans = i;
            break;
        }
    }
    return ans;
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        int n = 0;
        std::string s;
        std::cin >> n >> s;
        auto ss = s;
        std::reverse(s.begin(), s.end());
        std::cout << std::max(solve(n, ss), solve(n, s)) << '\n';
    }

    sp();

    return 0;
}
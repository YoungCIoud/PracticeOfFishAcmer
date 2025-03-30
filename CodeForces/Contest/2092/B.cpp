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

void solve()
{
    int n = 0;
    std::cin >> n;
    std::string s, t;
    std::cin >> s >> t;
    std::array<int, 2> cnt {};
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            cnt[i & 1]++;
        }
        if (t[i] == '0') {
            cnt[1 - (i & 1)]++;
        }
    }
    if (cnt[0] >= (n + 1 >> 1) && cnt[1] >= (n >> 1)) {
        std::cout << "Yes\n";
    }
    else {
        std::cout << "No\n";
    }
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
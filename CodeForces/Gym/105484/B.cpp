#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    #define cout cout << ">>>\t"
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
    std::string s;
    std::cin >> s;
    std::array<int, 3> cnt{};
    for (int i = 0; i < s.length(); i++) {
        if (i & 1 && s[i] != '2') {
            s[i] = s[i] ^ 1;
        }
        cnt[s[i] - '0']++;
    }
    int d = abs(cnt[0] - cnt[1]);
    int ans = 0;
    if (d >= cnt[2]) {
        ans = d - cnt[2];
    }
    else {
        ans = (d ^ cnt[2]) & 1;
    }
    std::cout << ans << '\n';
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
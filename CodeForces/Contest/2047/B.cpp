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
    std::string s;
    std::cin >> n >> s;
    std::vector cnt(26, 0);
    for (auto &c : s) {
        cnt[c - 'a']++;
    }
    int mn = -1, mx = -1;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] == 0) {
            continue;
        }
        if (mx == -1 || cnt[i] > cnt[mx]) {
            mx = i;
        }
        if (mn == -1 || cnt[i] <= cnt[mn]) {
            mn = i;
        }
    }
    for (auto &c : s) {
        if (c - 'a' == mn) {
            c = mx + 'a';
            break;
        }
    }
    std::cout << s << '\n';
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
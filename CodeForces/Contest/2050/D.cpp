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
    std::string s;
    std::cin >> s;
    for (int i = 0; i < s.length(); i++) {
        int mx = s[i], pos = i;
        for (int j = 1; j <= 9 && i + j < s.length(); j++) {
            if (s[i + j] - j > mx) {
                mx = s[i + j] - j;
                pos = i + j;
            }
        }
        for (int j = pos - 1; j >= i; j-- ) {
            s[j + 1] = s[j];
        }
        s[i] = mx;
    }
    std::cout << s << '\n';
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
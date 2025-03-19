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
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr u64 Mod = 1'0000'0000'0000'1029, MAX = -1;
constexpr int N = 5e5, Q = 5e5;

void solve() {
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        if (s[i - 1] == '1' && s[i] == '0') {
            cnt++;
        }
    }
    int ans = cnt * 2;
    if (s.back() == '1') {
        ans++;
    }
    std::cout << ans << '\n';
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
    return 0;
}

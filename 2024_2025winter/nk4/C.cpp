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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, M = 1e5, Inf = 1e9;

i64 qpow(i64 a, i64 p) {
    i64 res = 1;
    for (p; p; p >>= 1, a = a * a % Mod) {
        if (p & 1) {
            (res *= a) %= Mod;
        }
    }
    return res;
}

void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    int tot = 0;
    for (auto &c : s) {
        if (c == '?') {
            tot++;
        }
    }

    i64 ans = 0;
    if (s[0] == '?' || s.back() == '?') {
        if (n == 1) {
            ans = 2;
        }
        else {
            ans = n * qpow(2, tot - 1) % Mod;
        }
    }
    else if (s[0] == s.back()) {
        if (n == 1) {
            ans = 1;
        }
        else {
            ans = (n - 2) * qpow(2, tot) % Mod;
        }
    }
    else {
        ans = 2 * qpow(2, tot) % Mod;
    }

    std::cout << ans << '\n';
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
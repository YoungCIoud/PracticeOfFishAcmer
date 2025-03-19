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

bool is_a(std::string s) {
    std::vector cnt(26, 0);
    for (auto &c : s) {
        if (cnt[c - 'a']++ == 1) {
            return false;
        }
    }
    return true;
}

bool is_b(std::string s) {
    for (int i = 0; i + i < s.size(); i++) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

bool solve()
{
    std::string s;
    std::cin >> s;
    
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == s.back() && is_a(s.substr(0, i)) && is_b(s.substr(i, s.size() - i))) {
            return true;
        }
    }

    return false;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        std::cout << (solve() ? "HE" : "NaN") << '\n';
    }

    sp();

    return 0;
}
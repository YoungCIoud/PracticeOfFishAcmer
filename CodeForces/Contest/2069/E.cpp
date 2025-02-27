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

bool solve()
{
    std::string s;
    std::cin >> s;
    std::array<int, 4> n;
    std::cin >> n[0] >> n[1] >> n[2] >> n[3];

    std::string t{};
    for (int i = 1; i + 1 < s.length(); i++) {
        if (s[i] != s[i - 1] || s[i] != s[i] + 1) {
            t.push_back(s[i]);
            n[s[i] == 'B']--;
        }
    }
    if (s.length() == 1) {
        n[s[0] == 'B']--;
    }
    else
    {
        if (s[0] == s[1]) {
            n[s[0] == 'B']--;
        }
        else {
            t = s[0] + t;
        }
        if (s.back() == s[s.length() - 2]) {
            n[s.back() == 'B']--;
        }
        else {
            t = t + s.back();
        }
    } 

    if (n[0] < 0 || n[1] < 0) {
        return false;
    }

    std::vector str(4, std::vector<int>{});
    char fst = t[0], lst = t[0];
    int len = 1;
    for (int i = 1; i < t.length(); i++) {
        if (t[i] == lst) {
            if (fst == lst) {
                str[fst == 'B'].push_back(len);
            }
            else {
                str[fst == 'A' ? 2 : 3].push_back(len);
            }
            len = 1;
        }
        else {
            len++;
            lst = t[i];
        }
    }
    if (fst == lst) {
        str[fst == 'B'].push_back(len);
    }
    else {
        str[fst == 'A' ? 2 : 3].push_back(len);
    }
    for (auto &v : str) {
        if (not v.empty()) {
            std::sort(v.begin(), v.end());
        }
    }
    
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
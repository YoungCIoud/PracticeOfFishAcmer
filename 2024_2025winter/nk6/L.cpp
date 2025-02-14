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
std::string T = "CHICKEN";

bool solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    std::vector cnt(26, 0);
    int p = 0;
    for (auto &c : s) {
        cnt[c - 'A']++;
        if (p < T.size() && c == T[p]) {
            p++;
        }
    }
    
    if (p != T.size()) {
        return false;
    }
    
    for (auto &c : T) {
        cnt[c - 'A']--;
    }
    std::sort(cnt.begin(), cnt.end());
    n -= T.size();
    if (cnt.back() * 2 > n) {
        return false;
    }
    else {
        return n % 2 == 0;
    }
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        std::cout << (solve() ? "YES\n" : "NO\n");
    }

    sp();

    return 0;
}
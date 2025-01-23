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
    int n = 0, m = 0;
    std::cin >> n >> m;
    int d = n - m;
    std::string ans;
    if (d == 0 || d > 26) {
        ans = "NO";
    }
    else if (m == 1) {
        if (n > 27) {
            ans = "NO";
        }
        else {
            std::string s;
            for (int i = 0, c = 'a'; i < n - 1; i++, c++) {
                s.push_back(char(c));
            }
            ans = "YES\n" + s + "a";
        }
    }
    else if (d + d >= n) {
        if (n > 56) {
            ans = "NO";
        }
        else {
            std::string s(n, '?');
            int l = d, r = n - 1 - d;
            s[0] = s[l] = 'a';
            s[n - 1] = s[r] = 'b';
            for (int i = 1, c = 'c'; i < l; i++) {
                if (s[i] == '?')
                {
                    s[i] = char(c++);
                }
            }
            for (int i = n - 2, c = 'c'; i > l; i--) {
                s[i] = char(c++);
            }
            ans = "YES\n" + s;
        }
    }
    else {
        std::string s(n - 2 * d, 'a');
        std::string ss{};
        for (int i = 0; i < d; i++) {
            ss.push_back('a' + i);
        }
        s = ss + s;
        std::reverse(ss.begin(), ss.end());
        ans = "YES\n" + (s + ss);
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

    sp();

    return 0;
}
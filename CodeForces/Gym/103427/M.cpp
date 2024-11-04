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
    int n = s.length();
    std::vector nxt(n + 1, 0);
    s = "#" + s;
    std::cout << 1 << ' ' << 1 << '\n';
    int head = 1, len = 1;
    for (int i = 2; i <= n; i++) {
        if (s[i] > s[head]) {
            head = i, len = 1;
            std::cout << i << ' ' << i << '\n';
            continue;
        }

        while (s[head + nxt[len]] < s[i]) {
            head = head + len - nxt[len];
            len = nxt[len];
        }
        if (s[head + nxt[len]] == s[i]) {
            nxt[len + 1] = nxt[len] + 1;
            len++;
        }
        else if (s[head + nxt[len]] > s[i]) {
            nxt[++len] = 0;
        }
        std::cout << head << ' ' << i << '\n';
    }
    return;
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    sp();

    return 0;
}
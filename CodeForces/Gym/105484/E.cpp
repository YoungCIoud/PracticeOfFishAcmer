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
    int n = 0, k = 0;
    std::string s;
    std::cin >> n >> k >> s;
    int g = 0;
    int cnt = 0;
    for (int i = 0; i + 7 <= n; i++) {
        if (s.substr(i,  7) == "nanjing") {
            cnt++;
        }
    }
    while (g < n && s[g] != 'g') {
        g++;
    }
    if (g < std::min({(int)s.size(), 6, k}) && s[g] == 'g') {
        bool ok = true;
        for (int i = 0; i < 7; i++) {
            if (s[(g - i + n) % n] != "gnijnan"[i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cnt++;
        }
    }
    std::cout << cnt << '\n';
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
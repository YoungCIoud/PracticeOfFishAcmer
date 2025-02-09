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
std::string a = "uwawauwa";
int l = a.length();
void solve()
{
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    std::vector pre(n, 0);
    pre[0] = (s[0] == 'u' ? 1 : 0);
    for (int i = 1; i < n; i++) {
        pre[i] = pre[i - 1] + (s[i] == 'u' ? 1 : 0);
    }
    int ans = 0;
    for (int i = 2; i + l <= n; i++) {
        if (s.substr(i, l) == a) {
            ans += pre[i - 2];
            i += 4;
        }
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
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
constexpr int N = 1e5, M = 4000, Inf = 1e9;
int cnt[M + 5];

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cnt[i] = 1;
    }
    std::string s;
    for (int i = 0; i < n; i++) {
        std::cin >> s;
        for (int j = 0; j < m; j++) {
            int c = s[j] - '0';
            if (c == 0) {
                cnt[j] = 0;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < m; i++) {
        if (cnt[i]) {
            ans++;
        }
    }
    std::cout << ans << '\n';
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}

/*
3 3
100
110
111
*/
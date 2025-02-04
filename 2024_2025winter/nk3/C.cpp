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
constexpr int N = 1e5, M = 1e6, Inf = 1e9;
int tr[M + 1][26], tot;

void insert(std::string s) {
    int cur = 0;
    for (auto &c : s) {
        if (tr[cur][c - 'a'] == 0) {
            tr[cur][c - 'a'] = ++tot;
        }
        cur = tr[cur][c - 'a'];
    }
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        mx = std::max(mx, int(s.length()));
        insert(s);
    }
    int l = 0, r = 0;
    std::cin >> l >> r;
    std::cout << tot * 2 - mx << '\n';
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
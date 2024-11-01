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
constexpr int N = 2e5, M = 1e5, Inf = 1e9;
int tr[N + 5][27][2], cnt;

int insert(std::string s) {
    int len = s.length();
    int ans = s.length();

    int cur = 0;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j <= 26; j++) {
            if (tr[cur][j][0]) {
                ans = std::min(ans, len - i + tr[cur][j][1]);
            }
        }
        int to = s[i] - 'a';
        if (tr[cur][to][0] == 0) {
            tr[cur][to][0] = ++cnt;
            tr[cur][to][1] = len - i;
        }
        else {
            tr[cur][to][1] = std::min(tr[cur][to][1], len - i);
        }
        cur = tr[cur][to][0];
    }
    for (int j = 0; j <= 26; j++) {
        if (tr[cur][j][0]) {
            ans = std::min(ans, tr[cur][j][1]);
        }
    }
    tr[cur][26][0] = N;
    return ans;
}

void solve()
{
    int n = 0;
    std::cin >> n;
    while (n--) {
        std::string s;
        std::cin >> s;
        std::cout << insert(s) << '\n';
    }
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
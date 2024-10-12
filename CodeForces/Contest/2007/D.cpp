#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;
std::vector<int> g[N + 5];

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    std::string s;
    std::cin >> s;
    std::vector cnt(4, 0);
    for (int i = 1; i < n; i++) {
        if (g[i + 1].size() == 1) {
            if (s[i] == '?') {
                cnt[2]++;
            }
            else {
                cnt[s[i] - '0']++;
            }
        }
        else if (s[i] == '?') {
            cnt[3]++;
        }
    }
    int ans = 0;
    if (s[0] == '?') {
        if (cnt[0] != cnt[1]) {
            ans = std::max(cnt[0], cnt[1]) + (cnt[2]) / 2;
        }
        else {
            if (cnt[3] & 1) {
                ans = cnt[0] + (cnt[2] + 1) / 2;
            }
            else {
                ans = cnt[0] + cnt[2] / 2;
            }
        }
    }
    else {
        ans = cnt[(s[0] - '0') ^ 1] + (cnt[2] + 1) / 2;
    }
    std::cout << ans << '\n';
}

int main()
{
    // IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
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

std::array<char, 3> S = { 'L', 'I', 'T' };
int idx['Z'];

void solve()
{
    std::vector cnt('Z', 0);
    int n = 0;
    std::string s;
    std::cin >> n >> s;
    for (auto &c : s) {
        cnt[c]++;
    }
    if (cnt['L'] == n || cnt['I'] == n || cnt['T'] == n) {
        std::cout << -1 << '\n';
        return;
    }
    if (cnt['L'] == cnt['I'] && cnt['I'] == cnt['T']) {
        std::cout << 0 << '\n';
        return;
    }

    int mn = std::min({ cnt['L'], cnt['I'], cnt['T'] });
    std::vector<int> ans;

    int pos = 0;
    while (pos + 1< n && (cnt[s[pos]] == mn || s[pos] == s[pos + 1])) {
        pos++;
    }
    
    if (pos + 1 == n) { // 说明数量等于 mn 的有两个，且另外一个都在串的后面
        pos = 0;
        while (s[pos] == s[pos + 1]) {
            pos++;
        }
        ans.push_back(pos);
        int mx = std::max({ cnt['L'], cnt['I'], cnt['T'] }) + 1;
        while (mx > mn) {
            ans.push_back(pos + 1);
            ans.push_back(pos + 1);
            mx--;
        }
    }
    else {
        while (cnt[s[pos]] > mn) {
            ans.push_back(pos);
            ans.push_back(pos);
            cnt[s[pos]]--;
        }
        while (cnt[s[pos + 1]] > mn) {
            ans.push_back(pos + 1);
            ans.push_back(pos + 1);
            cnt[s[pos + 1]]--;
        }
        while (cnt[S[3 - idx[s[pos]] - idx[s[pos + 1]]]] > mn) {
            ans.push_back(pos + 2);
            ans.push_back(pos + 2);
            cnt[S[3 - idx[s[pos]] - idx[s[pos + 1]]]]--;
        }
    }

    assert(ans.size() <= 2 * n);
    std::cout << ans.size() << '\n';
    for (auto &i : ans) {
        std::cout << i + 1 << '\n';
    }
    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;

    idx['L'] = 0;
    idx['I'] = 1;
    idx['T'] = 2;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
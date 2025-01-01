#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    // #define cout cout << ">>>\t"
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
    int n = 0, m = 0, k = 0, w = 0;
    std::cin >> n >> m >> k >> w;
    std::vector row(n + m + 2, std::pair<int, bool>{});
    for (int i = 0; i < n; i++) {
        std::cin >> row[i].first;
        row[i].second = true;
    }
    for (int i = n; i < n + m; i++) {
        std::cin >> row[i].first;
        row[i].second = false;
    }
    row[n + m] = { 0, false };
    row[n + m + 1] = { w + 1, false };
    std::sort(row.begin(), row.end());

    int p = 0, q = 1;
    std::stack<std::pair<int, int>> stk;
    while (row[q].second) {
        q++;
    }
    while (q <= n + m + 1) {
        if (p + 1 != q) {
            int left = row[p + 1].first - row[p].first;
            int l = p + 1;
            while (l < q) {
                stk.push({ row[l].first, 1 });
                while (row[l].second && row[l].first < stk.top().first + k) {
                    l++;
                }
            }
            while (stk.top().first + stk.top().second * k > row[q].first) {
                auto cur = stk.top();
                stk.pop();
                if  (stk.empty() || stk.top().first < row[p].first) {
                    if (cur.first + cur.second * k - left >= row[q].first) {
                        std::cout << -1 << '\n';
                        return;
                    }
                    else {
                        int delta = (cur.first + cur.second * k) - row[q].first;
                        stk.push({ row[p].first + left - delta, cur.second });
                    }
                }
                else {
                    if (stk.top().first + (stk.top().second + cur.second) * k > row[q].first) {
                        stk.top().second += cur.second;
                    }
                    else {
                        left = cur.first - (stk.top().first + stk.top().second * k);
                        int delta = (cur.first + cur.second * k) - row[q].first;
                        stk.push({ stk.top().first + stk.top().second * k + left - delta, cur.second });
                    }
                }
            }
        }

        p = q;
        q++;
        while (q <= n + m + 1 && row[q].second) {
            q++;
        }
    }
    
    std::stack<int> ans;
    while (not stk.empty()) {
        auto &cur = stk.top();
        for (int i = cur.second - 1; ~i; i--) {
            ans.push(cur.first + i * k);
        }
        stk.pop();
    }
    std::cout << ans.size() << '\n';
    while (not ans.empty()) {
        std::cout << ans.top() << ' ';
        ans.pop();
    }
    std::cout << '\n';
    return;
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
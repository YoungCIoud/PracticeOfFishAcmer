#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::stack<std::pair<i64, int>> stk;
    for (int i = 0; i < n; i++) {
        i64 sum = 0;
        int cnt = 1;
        std::cin >> sum;

        while (not stk.empty() && stk.top().first >= sum / cnt) {
            sum += stk.top().first * stk.top().second;
            cnt += stk.top().second;
            stk.pop();
        }
        stk.push({ sum / cnt, cnt - sum % cnt});
        if (sum % cnt) {
            stk.push({ sum / cnt + 1, sum % cnt});
        }
    }
    i64 ans = stk.top().first;
    while (stk.size() > 1) {
        stk.pop();
    }
    std::cout << ans - stk.top().first << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
/*
5
5 14 4 10 2
*/
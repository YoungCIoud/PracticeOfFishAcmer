#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::priority_queue<i64> q;
    for (int i = 0; i < n; i++)
    {
        int u;
        std::cin >> u;
        q.push(u);
    }

    if (k == 1)
    {
        std::cout << q.top();
        return;
    }

    i64 ans = q.top(), sum = 0;
    while (!q.empty())
    {
        sum++;
        int cur = q.top();
        q.pop();
        cur /= k;
        if (cur) q.push(cur);
       // std::cout << q.top() << "\n";
        ans = std::min(ans, sum + (q.empty() ? 0 : q.top()));
        //if (q.top() == 1) break;
    }
    std::cout << ans << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    //std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
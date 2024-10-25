#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector s(n, std::array<i64, 2>{});
    for (auto &[a, b] : s) {
        std::cin >> a;
    }
    for (auto &[a, b] : s) {
        std::cin >> b;
    }
    std::sort(s.begin(), s.end(), [](std::array<i64, 2> &a, std::array<i64, 2> &b){
        if (a[0] == b[0]) {
            return a[1] < b[1];
        }
        else {
            return a[0] < b[0];
        }
    });

    std::priority_queue<i64> q;
    i64 sum = 0;
    for (int i = 0; i < k; i++) {
        q.push(s[i][1]);
        sum += s[i][1];
    }
    i64 ans = sum * s[k - 1][0];
    for (int i = k; i < n; i++) {
        if (s[i][1] < q.top()) {
            sum += s[i][1] - q.top();
            q.pop();
            q.push(s[i][1]);
            ans = std::min(ans, s[i][0] * sum);
        }
    }
    std::cout << ans << '\n';
    
    return;
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
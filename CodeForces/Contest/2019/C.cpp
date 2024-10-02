#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 2e5, M = 1e5;

void solve()
{
    int n = 0;
    i64 k = 0;
    std::cin >> n >> k;
    std::vector<i64> a(n);
    i64 sum = 0;
    for (auto &i : a) {
        std::cin >> i;
        sum += i;
    }
    std::sort(a.begin(),a.end(), std::greater<i64>());

    for (int i = n; i >= 1; i--) {
        i64 len = std::max(a[0], (sum + i - 1) / i);
        if (sum + k >= len * i) {
            std::cout << i << '\n';
            break;
        }
    }
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
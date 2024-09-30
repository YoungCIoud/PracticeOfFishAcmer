#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0, m = 0, q = 0;
    std::cin >> n >> m >> q;
    std::vector<int> pos(m);
    for (int &i : pos) {
        std::cin >> i;
    }
    std::sort(pos.begin(), pos.end());
    
    while (q--) {
        int a = 0;
        std::cin >> a;
        auto it = std::upper_bound(pos.begin(), pos.end(), a);
        int ans = 0;
        if (it == pos.end()) {
            ans = n - pos.back();
        }
        else if (it == pos.begin()) {
            ans = pos.front() - 1;
        }
        else {
            ans = (*it - *(it - 1)) / 2;
        }
        std::cout << ans << '\n';
    }
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
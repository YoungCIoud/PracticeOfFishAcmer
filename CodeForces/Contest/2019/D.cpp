#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 2e5, M = 1e5;

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector a(n, 0), fst(n, -1), lst(n, -1);
    int mn = n, mx = -1;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
        mn = std::min(a[i], mn);
        mx = std::max(a[i], mx);
        if (fst[a[i]] == -1) {
            fst[a[i]] = i;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (lst[a[i]] == -1) {
            lst[a[i]] = i;
        }
    }

    int L = -1, R = n;
    for (int i = mn, l = n, r = -1; i <= mx; i++) {
        if (fst[i] == -1) {
            continue;
        }
        l = std::min(l, fst[i]);
        r = std::max(r, lst[i]);
        if (r - l > i) {
            std::cout << 0 << '\n';
            return;
        }
        L = std::max(L, r - i);
        R = std::min(R, l + i);
    }

    std::cout << R - L + 1 << '\n';
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
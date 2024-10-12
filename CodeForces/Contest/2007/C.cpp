#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

void solve()
{
    int n = 0;
    i64 a = 0, b = 0;
    std::cin >> n >> a >> b;
    i64 g = std::__gcd(a, b);
    std::vector<i64> A(n);
    for (i64 &i : A) {
        std::cin >> i;
        i %= g;
    }

    std::sort(A.begin(), A.end());
    i64 ans = A.back() - A.front();
    A.push_back(A.front() + g);
    for (int i = 0; i < n; i++) {
        ans = std::min(ans, A[i] - A[i + 1] + g);
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
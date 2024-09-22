#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 2e5, M = 1e9;
int n;
vct<int> X(N + 5);
vct<i64> P(N + 5);  // 后缀和

void solve()
{
    int l = 0, r = 0;
    std::cin >> l >> r;
    int p = std::lower_bound(X.begin(), X.begin() + n + 2, l) - X.begin();
    int q = std::upper_bound(X.begin(), X.begin() + n + 2, r) - X.begin();
    if (p >= q) std::cout << "0\n";
    else std::cout << (P[p] - P[q]) << '\n';
    
}

int main()
{
    IOS;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> X[i];
    for (int i = 1; i <= n; i++) std::cin >> P[i];
    for (int i = n; i >= 1; i--) P[i] += P[i + 1];
    X[n + 1] = 1e9 + 1, X[0] = -X[n + 1];

    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
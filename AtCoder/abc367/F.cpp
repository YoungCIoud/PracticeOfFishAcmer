#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18, P = (1ll << 61) - 1;
constexpr int N = 1e5, M = 1e5;

std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    vct<int> A(n + 1), B(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> A[i];
    for (int i = 1; i <= n; i++) std::cin >> B[i];

    vct<i64> r(n + 1);
    for (int i = 1; i <= n; i++) r[i] = rnd() % P;
    
    vct<i64> pA(n + 1, 0), pB(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        pA[i] = (pA[i - 1] + r[A[i]]) % P;
        pB[i] = (pB[i - 1] + r[B[i]]) % P;
    }

    while (q--)
    {
        int l = 0, r = 0, u = 0, v = 0;
        std::cin >> l >> r >> u >> v;
        if ((pA[r] - pA[l - 1] + P) % P != (pB[v] - pB[u - 1] + P) % P) puts("No");
        else puts("Yes"); 
    }
}

int main()
{
    IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
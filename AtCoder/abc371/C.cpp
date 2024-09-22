#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 8, M = 1e5;
int n;
int A[N + 5][N + 5];
bool gm[N + 5][N + 5], gh[N + 5][N + 5];

void read(bool g[N + 5][N + 5])
{
    int m = 0;
    std::cin >> m;
    while (m--)
    {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g[u][v] = true;
        g[v][u] = true;
    }
}

void solve()
{
    std::cin >> n;
    read(gm), read(gh);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            std::cin >> A[i][j];
            A[j][i] = A[i][j];
        }
    
    vct<int> p(n + 1);
    for (int i = 1; i <= n; i++) p[i] = i;

    int ans = 0x3f3f3f3f;
    do
    {
        int cost = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (gm[i][j] ^ gh[p[i]][p[j]])
                    cost += A[p[i]][p[j]];
        if (ans > cost)
            ans = cost;
        
    } while (std::next_permutation(p.begin() + 1, p.end()));
    std::cout << ans / 2 << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
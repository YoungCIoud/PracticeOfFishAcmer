#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

class DSU
{
public:
    DSU(int x): size(x)
    {
        fa.assign(x + 1, 0);
        for (int i = 1; i <= x; i++) fa[i] = i;
    }

    int getfa(int u)
    {
        return u == fa[u] ? u : (fa[u] = getfa(fa[u]));
    }
    // 将u合并到v上
    void merge(int u, int v)
    {
        fa[getfa(u)] = getfa(v);
    }

    bool connected()
    {
        for (int i = 2; i <= size; i++)
            if (getfa(i) != getfa(i - 1)) return false;
        return true;
    }

    bool connected(int u, int v)
    {
        return getfa(u) == getfa(v);
    }
private:
    int size;
    vct<int> fa;
};

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    vct<int> ans(m + 1, 0);
    vct<DSU> dsu(m / (n - 1) + 5, n);
    for (int i = 1; i <= m; i++)
    {
        int u = 0, v = 0;
        std::cin >> u >> v;

        int l = 1, r = m / (n - 1);
        if (dsu[r].connected(u, v)) continue;
        while (l <= r)
        {
            int m = l + r >> 1;
            if (dsu[m].connected(u, v)) l = m + 1;
            else r = m - 1;
        }
        dsu[l].merge(u, v);
        ans[i] = l;
    }

    vct<bool> ok(m / (n - 1) + 1, false);
    for (int i = 1; i < ok.size(); i++)
        ok[i] = dsu[i].connected();

    for (int i = 1; i <= m; i++)
        std::cout << (ok[ans[i]] ? ans[i] : -1) << " \n"[i == m];
    return;
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
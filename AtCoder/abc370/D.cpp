#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

class BIT
{
public:
    BIT(int _n = 0): n(_n)
    {
        t.assign(n + 1, 0);
        for (int i = 1; i <= n; i++)
            add(i, 1);
    }
    void add(int pos, int val)
    {
        if (pos <= 0) return;
        while (pos <= n)
        {
            t[pos] += val;
            pos += lowbit(pos);
        }
    }
    int sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
    int findr(int l)
    {
        if (sum(l, n) == 0) return -1;
        int p = l, q = n;
        while (p <= q)
        {
            int m = p + q >> 1;
            if (sum(l, m) < 1) p = m + 1;
            else q = m - 1;
        }
        return p;
    }
    int findl(int r)
    {
        if (sum(1, r) == 0) return -1;
        int p = 1, q = r;
        while (p <= q)
        {
            int m = p + q >> 1;
            if (sum(m, r) < 1) q = m - 1;
            else p = m + 1;
        }
        return q;
    }
private:
    vct<int> t;
    int n;

    int lowbit(int x)
    {
        return x & (-x);
    }
    int sum(int x)
    {
        int res = 0;
        while (x > 0)
        {
            res += t[x];
            x -= lowbit(x);
        }
        return res;
    }
};

void solve()
{
    int n = 0, m = 0, q = 0;
    std::cin >> n >> m >> q;
    vct hor(n + 1, BIT(m)), ver(m + 1, BIT(n));

    while (q--)
    {
        int x = 0, y = 0;
        std::cin >> x >> y;
        int pl = hor[x].findl(y), pr = hor[x].findr(y);
        if (pl == pr && ~pl)
        {
            hor[x].add(y, -1);
            ver[y].add(x, -1);
            continue;
        }

        if (~pl)
            hor[x].add(pl, -1), ver[pl].add(x, -1);
        if (~pr)
            hor[x].add(pr, -1), ver[pr].add(x, -1);
        // printf("(%d, %d, %d)\t", pl, y, pr);

        int pu = ver[y].findl(x), pd = ver[y].findr(x);
        if (~pu)
            ver[y].add(pu, -1), hor[pu].add(y, -1);
        if (~pd)
            ver[y].add(pd, -1), hor[pd].add(y, -1);
        // printf("(%d, %d, %d)\n", pu, x, pd);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += hor[i].sum(1, m);
    std::cout << ans << '\n';
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
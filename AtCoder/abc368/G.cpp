#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e9;
// 区间和 编号
typedef std::pair<i64, int> Node;
Node operator+(const Node &a, const Node &b)
{
    return Node{ a.first + b.first, std::min(a.second, b.second) };
}
Node tr[N * 4];

int A[N + 5], B[N + 5];

void push_up(int cur)
{
    tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
}

void build(int cur, int l, int r)
{
    if (l == r)
        return void(tr[cur] = { A[l], B[l] == 1 ? M : l });
    
    int m = l + r >> 1;
    build(cur << 1, l, m);
    build(cur << 1 | 1, m + 1, r);

    push_up(cur);
    return;
}

void upd(int cur, int l, int r, int pos, Node val)
{
    if (l == r)
    {
        A[l] = val.first;
        B[l] = val.second;
        tr[cur] = { A[l], B[l] == 1 ? M : l };
        return;
    }

    int m = l + r >> 1;
    if (pos <= m) upd(cur << 1, l, m, pos, val);
    else upd(cur << 1 | 1, m + 1, r, pos, val);

    push_up(cur);
    return;
}

Node quiry(int cur, int l, int r, int sl, int sr)
{
    if (sl <= l && r <= sr) return tr[cur];

    int m = l + r >> 1;
    if (sr <= m) return quiry(cur << 1, l, m, sl, sr);
    else if (sl > m) return quiry(cur << 1 | 1, m + 1, r, sl, sr);
    else return quiry(cur << 1, l, m, sl, sr) + quiry(cur << 1 | 1, m + 1, r, sl, sr);
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> A[i];
    for (int i = 1; i <= n; i++) std::cin >> B[i];

    build(1, 1, n);
    
    int q = 0;
    std::cin >> q;
    while (q--)
    {
        int ope = 0, l = 0, r = 0;
        std::cin >> ope >> l >> r;
        
        if (ope == 1)
        {
            upd(1, 1, n, l, { r, B[l] });
        }
        else if(ope == 2)
        {
            upd(1, 1, n, l, { A[l], r });
        }
        else
        {
            i64 v = 0;
            while (l <= r)
            {
                int nex_l = std::min( r + 1, quiry(1, 1, n, l, n).second);
                
                if (l != nex_l) v += quiry(1, 1, n, l, nex_l - 1).first;
                if (nex_l <= r) v = std::max( v + A[nex_l], v * B[nex_l]);

                l = nex_l + 1;
            }
            std::cout << v << '\n';
        }
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
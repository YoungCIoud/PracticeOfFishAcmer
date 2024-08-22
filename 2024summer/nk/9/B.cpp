#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Inf = 1e18;
constexpr int N = 2e5, Mod = 998244353, M = 1e5;

struct Node
{
    int mn = 0, ans = 0;
    int tag = 0;
    
    Node operator+ (Node x)
    {
        x.tag = 0;
        if (mn == x.mn) x.ans = (ans + x.ans) % Mod;
        else if (mn < x.mn) x.mn = mn, x.ans = ans;
        return x; 
    }
} tr[N * 4 + 5];

void push_up(int cur)
{
    tr[cur] = tr[cur << 1] + tr[cur << 1 | 1];
}

void push_down(int cur)
{
    int &t = tr[cur].tag;
    Node &l = tr[cur << 1], &r = tr[cur << 1 | 1];

    l.mn += t, l.tag += t;
    r.mn += t, r.tag += t;
    t = 0;
}

// 区间修改
void upd(int cur, int l, int r, int sl, int sr, int val)
{
    if (sl <= l && r <= sr)
    {
        tr[cur].mn += val;
        tr[cur].tag += val;
        return;
    }

    push_down(cur);

    int m = l + r >> 1;
    if (sl <= m) upd(cur << 1, l, m, sl, sr, val);
    if (m < sr) upd(cur << 1 | 1, m + 1, r, sl, sr, val);

    push_up(cur);
}

// 单点修改
void upd(int cur, int l, int r, int pos, int val)
{
    if (l == r) return void(tr[cur].ans = val);

    push_down(cur);

    int m = l + r >> 1;
    if (pos <= m) upd(cur << 1, l, m, pos, val);
    else upd(cur << 1 | 1, m + 1, r, pos, val);

    push_up(cur);
}

void solve()
{
    int n = 0, m = 0;
    std::cin >> n >> m;
    vct<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    vct<int> S(m);
    for (int& i : S)
        std::cin >> i;

    vct dp(n + 1, 0);
    vct pos(n + 1, vct<int>(1, 0));
    upd(1, 0, n, 0, 1);
    
    auto ope = [&](int num, int val) -> void
    {
        int cnt = pos[num].size();
        for (auto& s : S)
            if (cnt > s)
                {
                    int l = pos[num][cnt - s - 1];
                    int r = pos[num][cnt - s] - 1;

                    // std::cout << l << " " << r << " " << val << "\n";

                    upd(1, 0, n, l, r, val);
                }
    };
    
    for (int i = 1; i <= n; i++)
    {
        ope(a[i], -1); // 撤销
        pos[a[i]].push_back(i);
        ope(a[i], 1); // 新增

        dp[i] = tr[1].ans;
        upd(1, 0, n, i, dp[i]);
    }

    std::cout << dp[n] << '\n';
}

int main()
{
    //IOS;
    int t = 1;
    //std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
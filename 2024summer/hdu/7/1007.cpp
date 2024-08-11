#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#define vct std::vector
#define ary std::array
#define str std::string

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18, M = 1e18, K = 1e18;
constexpr int N = 1e5;

// 线段树维护区间中存在的数的小标的最小值
struct
{
    int ls, rs, mn;
}tr[N * 80 + 5];
int cnt;

int quiry(int cur, i64 l, i64 r, i64 sl, i64 sr)
{
    if (!cur) return N + 5;
    if (sl <= l && r <= sr) return tr[cur].mn;

    i64 m = l + r >> 1;
    int mn = N + 5;
    if (m >= sl)
        mn = std::min(mn, quiry(tr[cur].ls, l, m, sl, sr));
    if (m < sr)
        mn = std::min(mn, quiry(tr[cur].rs, m + 1, r, sl, sr));
    
    return mn;
}

void upd(int cur, i64 l, i64 r, i64 val, int pos)
{
    tr[cur].mn = pos;
    if (l == r) return;

    i64 m = l + r >> 1;
    if (m >= val)
    {
        if (!tr[cur].ls)
            tr[cur].ls = ++cnt;
        upd(tr[cur].ls, l, m, val, pos);
    }
    else
    {
        if (!tr[cur].rs)
            tr[cur].rs = ++cnt;
        upd(tr[cur].rs, m + 1, r, val, pos);
    }
}

void solve()
{
    for (int i = 1; i <= cnt; i++)
        tr[i] = { 0, 0, 0 };
    cnt = 1;

    int n = 0;
    i64 m = 0, k = 0;
    std::cin >> n >> m >> k;
    vct<i64> a(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];

    // 后一个最近的满足条件的合法音符
    // nex[i][0]的条件是音高在[ai, ai - k]
    // nex[i][1]的条件是音高在[ai, ai + k]
    vct<ary<int, 2>> nex(n + 1);
    for (int i = n; i; i--)
    {
        nex[i][0] = quiry(1, 1ll, m, std::max(1ll, a[i] - k), a[i]);
        nex[i][1] = quiry(1, 1ll, m, a[i], std::min(m, a[i] + k));
        upd(1, 1ll, m, a[i], i);
    }

    int q = 0;
    std::cin >> q;

    vct<int> dp(n + 1, 1);
    while (q--)
    {
        int l = 0, r = 0;
        std::cin >> l >> r;
        
        for (int i = l; i <= r; i++)
            for (auto& to : nex[i])
                if (to && to <= r)
                    dp[to] = std::max(dp[to], dp[i] + 1);

        int ans = 0;
        for (int i = l; i <= r; i++)
        {
            ans = std::max(ans, dp[i]);
            dp[i] = 1;
        } 

        std::cout << (r - l + 1 - ans) << '\n';
    }

    return;
}

int main()
{
    IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
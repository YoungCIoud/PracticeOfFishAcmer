#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, Q = 2e5, Inf = 1e9;

int a[N], sp[N + 1], ans[Q];
std::vector<int> h;

std::vector<std::array<int, 3>> qr[N];

// Luogu P3919 查询区间第 k 大
struct Node {
    int l, r;
    int sum;
} tr[N << 5];
int cnt;

int New(int old) {
    tr[cnt] = tr[old];
    return cnt++;
}

void push_up(int cur) {
    auto &[l, r, sum] = tr[cur];
    sum = tr[l].sum + tr[r].sum;
}

int build(int l, int r) {
    int cur = cnt++;
    if (l + 1 == r) {
        return cur;
    }
    int m = l + r >> 1;
    tr[cur].l = build(l, m);;
    tr[cur].r = build(m, r);;
    return cur;
}

int upd(int old, int l, int r, int pos) {
    int cur = New(old);
    if (l + 1 == r) {
        tr[cur].sum++;
        return cur;
    }
    int m = l + r >> 1;
    if (m > pos) {
        tr[cur].l = upd(tr[cur].l, l, m, pos);
    }
    else {
        tr[cur].r = upd(tr[cur].r, m, r, pos);
    }

    push_up(cur);
    return cur;
}

int quiry(int lcur, int rcur, int l, int r, int k) {
    if (l + 1 == r) {
        return l;
    }

    int m = l + r >> 1;
    int num = tr[tr[rcur].l].sum - tr[tr[lcur].l].sum;
    if (num >= k) {
        return quiry(tr[lcur].l, tr[rcur].l, l, m, k);
    }
    else {
        return quiry(tr[lcur].r, tr[rcur].r, m, r, k - num);
    }
}

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    h.assign(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        h[i] = a[i];
    }
    std::sort(h.begin(), h.end());
    h.erase(std::unique(h.begin(), h.end()), h.end());
    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(h.begin(), h.end(), a[i]) - h.begin();
    }

    for (int i = 0; i < q; i++) {
        int l = 0, r = 0, k = 0;
        std::cin >> l >> r >> k;
        l--, r--;
        qr[r].push_back({ i, l, k });
    }

    int *const rt = sp + 1;
    rt[-1] = build(0, h.size());
    for (int r = 0; r < n; r++) {
        rt[r] = upd(rt[r - 1], 0, h.size(), a[r]);
        for (auto &[idx, l, k] : qr[r]) {
            ans[idx] = h[quiry(rt[l - 1], rt[r], 0, h.size(), k)];
        }
    }

    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << '\n';
    }
}

int main()
{
    IOS;
    int _t = 1;
    // std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    sp();

    return 0;
}
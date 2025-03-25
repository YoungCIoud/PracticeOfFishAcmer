#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define IOS
#else
    #define debug(...)
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, Q = 2e5, Inf = 1e9;

int a[N + 5];

int rt[N + 5], cnt;
// tr[i][2] AKA siz[i]
std::array<int, 3> tr[N << 5]; // about 32N

int New() {
    tr[cnt] = { 0, 0, 0 }; // init
    return cnt++;
}
void insert(int cur, int old, int x) {
    for (int i = 29; i >= 0; i--) {
        tr[cur][2] = tr[old][2] + 1;
        int b = x >> i & 1;
        tr[cur][b] = New(); // likewise, persistent segment-tree, create new node to insert or modify
        tr[cur][b ^ 1] = tr[old][b ^ 1];
        old = tr[old][b];
        cur = tr[cur][b];
    }
    tr[cur][2] = tr[old][2] + 1;
}
int ask(int l, int r, int x) {
    int ans = 0;
    for (int i = 29; ~i; i--) {
        int b = x >> i & 1;
        if (tr[tr[r][b ^ 1]][2] - tr[tr[l][b ^ 1]][2] > 0) {
            b ^= 1;
            ans |= (1 << i);
        }
        l = tr[l][b], r = tr[r][b];
    }
    return ans;
}

void solve()
{
    cnt = 1; // started from 1
    rt[0] = New();
    int n = 0, q = 0;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        rt[i] = New();
        insert(rt[i], rt[i - 1], a[i]);
    }
    for (int i = 0; i < q; i++) {
        int l = 0, r = 0, x = 0;
        std::cin >> l >> r >> x;
        std::cout << ask(rt[l - 1], rt[r], x) << '\n';
    }

    return;
}

int main()
{
    IOS;
    int _t = 1;
    std::cin >> _t;
    
    while (_t--)
    {
        solve();
    }

    return 0;
}
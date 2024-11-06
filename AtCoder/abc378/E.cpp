#include<bits/stdc++.h>
#ifdef LOCAL_MACHINE
    #define debug(...) printf(__VA_ARGS__)
    #define sp() system("pause")
    #define IOS
    #define cout cout << ">>>\t"
#else
    #define debug(...)
    #define sp()
    #define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)
#endif

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353;
constexpr int N = 2e5, M = 2e5, Inf = 1e9;
int n = 0, m = 0;
int tr[M + 5];
int lowbit(int x) {
    return x & (-x);
}
void add(int pos) {
    pos++;
    for (pos; pos <= m; pos += lowbit(pos)) {
        tr[pos]++;
    }
    return;
}
int cnt(int r) {
    int res = 0;
    for (r; r >= 1; r -= lowbit(r)) {
        res += tr[r];
    }
    return res;
}
int cnt(int l, int r) {
    return (l <= r) ? cnt(r + 1) - cnt(l) : 0;
}

void solve()
{
    std::cin >> n >> m;
    i64 ans = 0, pre = 0, sum = 0;
    add(0);
    for (int i = 1; i <= n; i++) {
        i64 a = 0;
        std::cin >> a;
        (pre += a) %= m;
        add(pre);
        ans += 1ll * pre * i - sum + 1ll * m * cnt(pre + 1, m - 1);
        sum += pre;
    }
    std::cout << ans << '\n';
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

    sp();

    return 0;
}
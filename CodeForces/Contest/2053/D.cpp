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
constexpr int N = 2e5, M = 1e5, Inf = 1e9;
std::pair<i64, int> a[N + 5], b[N + 5];
int pa[N + 5], pb[N + 5];

i64 qpow(i64 a, i64 p) {
    i64 res = 1;
    while (p) {
        if (p & 1) {
            (res *= a) %= Mod;
        }

        p >>= 1;
        (a *= a) %= Mod;
    }
    return res;
}

i64 inv(i64 a) {
    return qpow(a, Mod - 2);
}

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i].first;
        a[i].second = i;
    }
    std::sort(a, a + n);
    for (int i = 0; i < n; i++) {
        pa[a[i].second] = i;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i].first;
        b[i].second = i;
    }
    std::sort(b, b + n);
    for (int i = 0; i < n; i++) {
        pb[b[i].second] = i;
    }

    i64 ans = 1;
    for (int i = 0; i < n; i++) {
        (ans *= std::min(a[i].first, b[i].first)) %= Mod;
    }
    std::cout << ans << '\n';

    while (q--) {
        int op = 0, x = 0;
        std::cin >> op >> x;
        x--;
        
        if (op == 1) {
            // std::cout << a[pa[x]].first << " -> " << a[pa[x]].first + 1 << '\n';

            int cur = pa[x];
            int pos = std::upper_bound(a, a + n, std::make_pair(a[cur].first, Inf)) - a - 1;
            a[cur].first++;
            if (pos != cur) {
                std::swap(a[cur], a[pos]);
                std::swap(pa[a[cur].second], pa[a[pos].second]);
                cur = pos;
            }
            if (a[cur].first <= b[cur].first) {
                (ans *= inv(a[cur].first - 1) * a[cur].first % Mod) %= Mod;
            }
        }
        else {
            // std::cout << b[pb[x]].first << " -> " << b[pb[x]].first + 1 << '\n';

            int cur = pb[x];
            int pos = std::upper_bound(b, b + n, std::make_pair(b[cur].first, Inf)) - b - 1;
            b[cur].first++;
            if (pos != cur) {
                std::swap(b[cur], b[pos]);
                std::swap(pb[b[cur].second], pb[b[pos].second]);
                cur = pos;
            }
            if (b[cur].first <= a[cur].first) {
                (ans *= inv(b[cur].first - 1) * b[cur].first % Mod) %= Mod;
            }
        }

        std::cout << ans << ' ';
    }
    std::cout << '\n';
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
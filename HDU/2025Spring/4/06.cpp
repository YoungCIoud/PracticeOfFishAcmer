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
constexpr int N = 2e5;

int n = 0, q = 0;
int a[N + 5];
i64 tr[N + 5];

int lowbit(int x) {
    return x & -x;
}

void add(int pos, i64 val) {
    while (pos <= n) {
        tr[pos] += val;
        pos += lowbit(pos);
    }
    return;
}
i64 ask(int pos) {
    i64 res = 0;
    while (pos >= 1) {
        res += tr[pos];
        pos -= lowbit(pos);
    }
    return res / 100;
}

void solve()
{
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        tr[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        add(i, a[i]);
    }
    
    i64 ans = 0;
    int tim = 0;
    while (q--) {
        int op, x, y;
        std::cin >> op >> x >> y;
        if (op == 1) {
            add(x, y - a[x]);
            a[x] = y;
        }
        else {
            ans ^= 1ll * (++tim) * (ask(y) - ask(x - 1));
        }
    }
    std::cout << ans << '\n';
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

    sp();

    return 0;
}

/*
1
8 8
170 180 45 120 -100 134 161 -21 
2 4 4
1 1 28
2 3 8
1 5 -63
1 2 -41
2 5 5
1 3 90
2 3 8
*/
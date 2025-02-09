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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1e5, M = 1e5, Inf = 1e9, L = 30;

class BIT {
private:
    int n;
    std::vector<int> a;

    int lowbit(int x) {
        return x & -x;
    }
    
    int sum(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= lowbit(i)) {
            res += a[i];
        }
        return res;
    }
public:
    BIT(int _n) {
        n = _n;
        a.assign(n + 1, 0);
    }

    void add(int pos, int val) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            a[i] += val;
        }
    }

    int sum(int l, int r) {
        if (l > r) {
            return 0;
        }
        return sum(r) - sum(l - 1);
    }
};

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    
    std::vector v(n + 1, 0);
    std::vector a(L, BIT(n));
    std::vector b(L, BIT(n));
    for (int i = 1; i <= n; i++) {
        int x = 0;
        std::cin >> x;
        for (int bit = 0; bit < L; bit++) {
            if ((x >> bit) & 1) {
                b[bit].add(i, 1);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> v[i];
        for (int bit = 0; bit < L; bit++) {
            if ((v[i] >> bit) & 1) {
                a[bit].add(i, 1);
            }
        }
    }

    std::vector pre(n + 1, 0ll);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1];
        for (int bit = 0; bit < L; bit++) {
            i64 d = 0;
            i64 cntone = b[bit].sum(1, i);
            if ((v[i] >> bit) & 1) {
                d = ((i - cntone) << bit) % Mod;
            }
            else {
                d = (cntone << bit) % Mod;
            }
            (pre[i] += d) %= Mod;
        }
    }

    while (q--) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        i64 ans = (pre[r] + Mod - pre[l - 1]) % Mod;
        i64 d = 0;

        if (l != 1) {
            i64 w = r - l + 1, h = l - 1;
            for (int bit = 0; bit < L; bit++) {
                i64 acnt1 = a[bit].sum(l, r), acnt0 = w - acnt1;
                i64 bcnt1 = b[bit].sum(1, h), bcnt0 = h - bcnt1;
                (d += ((acnt1 * bcnt0 + acnt0 * bcnt1) << bit) % Mod) %= Mod;
            }
        }

        (ans += Mod - d) %= Mod;
        std::cout << ans << '\n';
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

    sp();

    return 0;
}
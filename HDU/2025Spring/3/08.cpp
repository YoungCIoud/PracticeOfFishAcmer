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

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 2e5, X = 2e5;

class BIT {
private:
    int n;
    std::vector<i64> tr;

    int lowbit(int x) {
        return x & -x;
    }

    i64 sum(int l) {
        i64 res = 0;
        while (l >= 1) {
            res += tr[l];
            l -= lowbit(l);
        }
        return res;
    }
public:
    BIT(int _n) : n(_n) {
        tr.assign(n + 1, 0ll);
    }
    void add(int pos, i64 val) {
        while (pos <= n) {
            tr[pos] += val;
            pos += lowbit(pos);
        }
    }
    i64 sum(int l, int r) {
        if (l > r) {
            return 0;
        }
        else {
            return (sum(r) - sum(l - 1)) % Mod;
        }
    }
};

i64 qpow(i64 a, i64 p) {
    i64 res = 1;
    while (p) {
        if (p & 1) {
            (res *= a) %= Mod;
        }

        (a *= a) %= Mod;
        p >>= 1;
    }
    return res;
}
i64 inv(i64 a) {
    return qpow(a, Mod - 2);
}

int a[N + 5], lst[N + 5], pos[N + 5];
i64 I[N + 5], A[N + 5];
i64 ans[N + 5];
std::vector qr(N + 5, std::vector<std::array<int, 2>>{});

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::fill(pos + 1, pos + 1 + n, 0);
    for (int i = 1; i <= n; i++) {
        qr[i].clear();

        std::cin >> a[i];
        lst[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    for (int i = 0; i < q; i++) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        qr[r].push_back({ l, i });
    }

    BIT L(n), R(n), LR(n), C(n);
    for (int r = 1; r <= n; r++) {
        if (lst[r] != 0) {
            L.add(lst[r], r - 1);
            R.add(lst[r], lst[r] + 1);
            LR.add(lst[r], -1);
            C.add(lst[r], -1ll * lst[r] * r + lst[r] -  r + 1);
        }

        for (auto &[l, idx] : qr[r]) {
            ans[idx] = A[r - l + 1];
            (ans[idx] += Mod - (L.sum(l, r) * l + R.sum(l, r) * r + LR.sum(l, r) * l * r + C.sum(l, r)) % Mod) %= Mod;
            (ans[idx] *= I[r - l + 1]) %= Mod;
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
    std::cin >> _t;

    for (int i = 1; i <= N; i++) {
        I[i] = inv((1ll * (i + 1) * i / 2ll) % Mod);
        A[i] = (1ll * i * (i + 1) * (i + 2) / 6ll) % Mod;
    }

    
    while (_t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
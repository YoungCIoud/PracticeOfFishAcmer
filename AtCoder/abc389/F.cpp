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
constexpr int N = 2e5, M = 5e5, Inf = 1e9;

class BIT {
private:
    int n;
    std::vector<int> a;

    int lowbit(int x) {
        return x & -x;
    }

    void upd(int p, int val) {
        if (p < 1 || p > n) {
            return;
        }
        for (int i = p; i <= n; i += lowbit(i)) {
            a[i] += val;
        }
        return;
    }

public:
    BIT(int _n): n(_n) {
        a.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            upd(i, 1);
        }
        return;
    }

    void upd(int l, int r, int val) {
        if (l > r) {
            return;
        }
        upd(l, val);
        upd(r + 1, -val);
        return;
    }

    int operator[](int idx) {
        int res = 0;
        for (int i = idx; 1 <= i && i <= n; i -= lowbit(i)) {
            res += a[i];
        }
        return res;
    }

    std::array<int, 2> bsearch(int x) {
        int l = 1, r = n;
        while (l <= r) {
            int m = l + r >> 1;
            if ((*this)[m] <= x) {
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }

        // l: first number that greater than x
        // r: last number that not greater than x;
        return { l, r };
    }
} t(M);

void solve()
{
    int n = 0;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        t.upd(t.bsearch(l - 1)[0], t.bsearch(r)[1], 1);
    }

    int q = 0;
    std::cin >> q;
    while (q--) {
        int x = 0;
        std::cin >> x;
        std::cout << t[x] << '\n';
    }
    return;
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
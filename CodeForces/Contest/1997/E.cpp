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
constexpr int N = 2e5, M = 2e5, Inf = 1e9;

class BIT {
public:
    BIT (int _n): n(_n) {
        t.assign(n + 1, 0);
    }
    // 区间[l, n]加1
    void add(int l) {
        while (l <= n) {
            t[l]++;
            l += lowbit(l);
        }
    }
    // 询问下标x的对应值
    int ask(int x) {
        int res = 0;
        while (x > 0) {
            res += t[x];
            x -= lowbit(x);
        }
        return res;
    }
private:
    int n;
    std::vector<int> t;

    int lowbit(int x) {
        return x & -x;
    }
};

void solve()
{
    int n = 0, q = 0;
    std::cin >> n >> q;
    std::vector a(n, 0);
    for (auto &i : a) {
        std::cin >> i;
    }
    std::vector qr(q, std::array<int, 3>{});
    for (int i = 0; i < q; i++) {
        std::cin >> qr[i][1] >> qr[i][2];
        qr[i][1]--;
        qr[i][0] = i;
    }
    std::sort(qr.begin(), qr.end(), [&](auto &u, auto &v){
        return u[1] < v[1];
    });

    std::vector ans(q, false);
    BIT num(n);
    int p = 0;
    for (int i = 0; i < n; i++) {
        while (p < q && qr[p][1] <= i) {
            ans[qr[p][0]] = num.ask(qr[p][2]) / qr[p][2] + 1 <= a[i];
            p++;
        }

        int l = 1, r = n;
        while (l <= r) {
            int m = l + r >> 1;
            if (num.ask(m) / m + 1 > a[i]) {
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        num.add(l);
    }

    for (int i = 0; i < q; i++) {
        std::cout << (ans[i] ? "YES" : "NO") << '\n';
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
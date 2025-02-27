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
constexpr int N = 5e5, M = 1e5, Inf = 1e9;

class BIT {
private:
    int n;
    std::vector<int> a;

    int lowbit(int x) {
        return x & -x;
    }
    int sum(int l) {
        int res = 0;
        for (int i = l; i >= 1; i -= lowbit(i)) {
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
        return sum(r) - sum(l - 1);
    }
};

void solve()
{
    int n = 0;
    std::cin >> n;
    BIT tr(n);
    std::vector p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        tr.add(i, 1);

        std::cin >> p[i];
    }

    std::vector ans(n + 1, 0);
    for (int i = n; i >= 1; i--) {
        int l = 1, r = n;
        while (l <= r) {
            int m = l + r >> 1;
            if (tr.sum(1, m) < p[i]) {
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        tr.add(l, -1);
        ans[l] = i;
    }
    
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << " \n"[i == n];
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
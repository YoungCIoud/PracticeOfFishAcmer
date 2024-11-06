#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 1e5, M = 1e5;

class BIT {
public:
    BIT(int _n = 0): n(_n) {
        tr.assign(n + 1, 0ll);
    }

    void add(int pos, i64 val) {
        for (pos; pos <= n; pos += lowbit(pos)) {
            tr[pos] += val;
        }
    }
    i64 sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
private:
    int n;
    std::vector<i64> tr;
    int lowbit(int x) {
        return x & (-x);
    }
    // sum[1, x];
    i64 sum(int x) {
        i64 val = 0;
        for (x; x > 0; x -= lowbit(x)) {
            val += tr[x];
        }
        return val;
    }
};

void test() {
    int n = 0, q = 0;
    std::cin >> n >> q;
    BIT T(n);
    for (int i = 1; i <= n; i++) {
        int a = 0;
        std::cin >> a;
        T.add(i, a);
    }
    while (q--) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        std::cout << T.sum(l, r) << '\n';
    }
}

void solve()
{
    int n = 0;
    std::cin >> n;
    BIT T(n);
    std::vector a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    std::cout << 0 << " \n"[1 == n];

    std::vector vis(n + 1, false);
    i64 ans = 0;
    int mx = a[1], cnt_mx = 1, cnt_low = 0;
    T.add(a[1], 1);
    vis[a[1]] = true;
    for (int k = 2; k <= n; k++) {
        if (a[k] < mx) {
            ans += T.sum(a[k] + 1, n);
            if (cnt_mx >= 2) {
                cnt_low++;
            }
        }
        else if (a[k] > mx) {
            ans++; // 第一步对答案的贡献
            ans += 1ll * cnt_mx; // 上一个最大值对答案的贡献
            ans += 1ll * cnt_low;
            
            cnt_mx = 1;
            cnt_low = 0;
            mx = a[k];
        }
        else {
            cnt_mx++;
        }

        std::cout << ans << " \n"[k == n];
        if (not vis[a[k]]) {
            vis[a[k]] = true;
            T.add(a[k],  1);
        }
    }
}

int main()
{
    // IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
        // test();
    }

    // system("pause");

    return 0;
}
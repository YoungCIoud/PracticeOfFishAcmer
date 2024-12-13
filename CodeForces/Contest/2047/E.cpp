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
constexpr int N = 1e5, M = 1e9, Inf = 1e9;

class BIT {
public:
    BIT(int _n): n(_n) {
        tr.assign(n + 1, 0);
    }
    void upd(int pos, int val) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            tr[i] += val;
        }
        return;
    }
    int ask(int l, int r) {
        return ask(r) - ask(l - 1);
    }
private:
    int n;
    std::vector<int> tr;

    int lowbit(int x) {
        return x & -x;
    }
    int ask(int l) {
        int res = 0;
        for (int i = l; i > 0; i -= lowbit(i)) {
            res += tr[i];
        }
        return res;
    }
};

void solve()
{
    int n = 0;
    std::cin >> n;
    std::vector<int> hx, hy;
    std::vector a(n, std::pair<int, int>{});
    for (auto &[x, y] : a) {
        std::cin >> x >> y;
        hx.push_back(x);
        hy.push_back(y);
    }
    std::sort(a.begin(), a.end());

    // 离散化 && 初始化
    std::sort(hx.begin(), hx.end());
    hx.erase(std::unique(hx.begin(), hx.end()), hx.end());
    std::sort(hy.begin(), hy.end());
    hy.erase(std::unique(hy.begin(), hy.end()), hy.end());
    BIT L(hy.size()), R(hy.size());
    for (auto &[x, y] : a) {
        x = std::lower_bound(hx.begin(), hx.end(), x) - hx.begin() + 1;
        y = std::lower_bound(hy.begin(), hy.end(), y) - hy.begin() + 1;
        R.upd(y, 1);
    }

    auto trans = [&](int x) -> void {
        int p = 0;
        for (int i = 19; i >= 0; i--) {
            if ((p | (1 << i)) < n && a[p | (1 << i)].first <= x) {
                p |= (1 << i);
            }
        }
        while (p >= 0 && a[p].first == x) {
            R.upd(a[p].second, -1);
            L.upd(a[p].second, 1);
            p--;
        }
    };
    std::array<int, 3> ans{ -Inf, -1, -1 };
    // 枚举 x0
    for (int x = 1; x <= hx.size(); trans(x), x++) {
        // 在 x0 确定的情况下二分最优的 y0
        int y = 0, mx = -Inf;
        int l = 1, r = hy.size();
        while (l <= r) {
            int mid = l + r >> 1;
            int up = std::min(L.ask(mid,hy.size()), R.ask(mid,hy.size()));
            int down = std::min(L.ask(1, mid - 1), R.ask(1, mid - 1));
            if (up <= down) {
                r = mid - 1;
                if (up > mx) {
                    y = mid;
                    mx = up;
                }
            }
            else {
                l = mid + 1;
                if (down > mx) {
                    y = mid;
                    mx = down;
                }
            }
        }
        if (mx > ans[0]) {
            ans = { mx, x, y };
        }
    }
    std::cout << ans[0] << '\n' << hx[ans[1] - 1] << ' ' << hy[ans[2] - 1] << '\n';
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
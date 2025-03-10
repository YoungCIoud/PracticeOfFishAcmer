#include <bits/stdc++.h>

#define IOS \
std::ios::sync_with_stdio(false);\
std::cin.tie(nullptr);\
std::cout.tie(nullptr);

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7, inv2 = 499122177;
constexpr int N = 1e5, M = 20, Inf = 1e9 + 10;

class st {
private:
    std::vector<std::array<std::array<int, 2>, M>> a;
    std::array<int, 2> getval(std::array<int, 2> &u, std::array<int, 2> &v) {
        return { std::min(u[0], v[0]), std::max(u[1], v[1]) };
    }
public:
    st() {
        insert(0);
    }
    void insert(int val) {
        a.push_back(std::array<std::array<int, 2>, M>{});
        int R = a.size() - 1;
        a[R][0] = { val, val };
        for (int l = 1; l < M; l++) {
            if (R - (1 << l) >= 0) {
                a[R][l] = getval(a[R][l - 1], a[R - (1 << l - 1)][l - 1]);
            }
        }
    }

    std::array<int, 2> ask(int l, int r) {
        if (l > r) {
            return { -1, -1 };
        }
        int len = log2(r - l + 1);
        return getval(a[l + (1 << len) - 1][len], a[r][len]);
    }
};

int main () {
    IOS

    int _t = 1;
    std::cin >> _t;
    while (_t--) {
        int n = 0, q = 0;
        std::cin >> n >> q;
        std::vector<i64> h(n + 1, 0);
        st ob, ev;
        for (int i = 1; i <= n; i++) {
            std::cin >> h[i];
            if (i & 1) {
                ob.insert(h[i]);
            }
            else {
                ev.insert(h[i]);
            }
        }
        std::vector L(n + 1, 0);
        st len;
        for (int l = 1, r = 1; r <= n; r++) {
            auto obb = ob.ask(l + 2 >> 1, r + 1 >> 1);
            auto eve = ev.ask(l + 1 >> 1, r >> 1);
            // 海浪区间满足区间中奇数位的最小值大于偶数位的最大值 或 奇数位的最大值小于偶数位的最小值
            while (l < r && obb[0] <= eve[1] && obb[1] >= eve[0]) {
                l++;
                obb = ob.ask(l + 2 >> 1, r + 1 >> 1);
                eve = ev.ask(l + 1 >> 1, r >> 1);
            }
            L[r] = l;
            len.insert(r - l + 1);
        }

        i64 ans = 0;
        for (int i = 1; i <= q; i++) {
            int l = 0, r = 0;
            std::cin >> l >> r;

            int ll = l, rr = r;
            while (ll <= rr) {
                int mid = ll + rr >> 1;

                if (L[mid] <= l) {
                    ll = mid + 1;
                }
                else {
                    rr = mid - 1;
                }
            }

            int le = std::max(rr - l + 1, len.ask(ll, r)[1]);
            // std::cout << le << '\n';
            (ans += 1ll * i * le) %= Mod;
        }
        std::cout << ans << '\n';
    }

    system("pause");

    return 0;
}
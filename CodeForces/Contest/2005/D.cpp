#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 2e5, M = 1e5;
// 数组 gcd前缀 gcd后缀
std::vector<int> a(N + 5), pa(N + 5), sa(N + 5);
std::vector<int> b(N + 5), pb(N + 5), sb(N + 5);

std::array<i64, 2> max(std::array<i64, 2> L, std::array<i64, 2> R) {
    if (R[0] > L[0]) {
        L = R;
    }
    else if (R[0] == L[0]) {
        L[1] += R[1];
    }
    return L;
}

std::array<i64, 2> cnt(int l, int r) {
    if (l == r) {
        int va = std::__gcd(b[l], std::__gcd(pa[l - 1], sa[l + 1]));
        int vb = std::__gcd(a[l], std::__gcd(pb[l - 1], sb[l + 1]));
        return { va + vb, 1 };
    }

    int m = l + r >> 1;
    std::array<i64, 2> L = cnt(l, m), R = cnt(m + 1, r);
    L = max(L, R);
    R = { 0, 0 };
    
    // 区间端点在中点异侧
    // 枚举左端点
    // la lb lcnt
    std::map<std::pair<int, int>, i64> cntl;
    int ga = 0, gb = 0;
    for (int i = m; i >= l; i--) {
        ga = std::__gcd(ga, a[i]);
        gb = std::__gcd(gb, b[i]);

        cntl[{ std::__gcd(pa[i - 1], gb), std::__gcd(pb[i - 1], ga) }]++;
    }

    // 枚举右端点
    // ra rb rcnt
    std::map<std::pair<int, int>, i64> cntr;
    ga = 0, gb = 0;
    for (int i = m + 1; i <= r; i++) {
        ga = std::__gcd(ga, a[i]);
        gb = std::__gcd(gb, b[i]);

        cntr[{ std::__gcd(sa[i + 1], gb), std::__gcd(sb[i + 1], ga)} ]++;
    }

    // 合并
    for (auto &[lval, lcnt] : cntl) {
        auto &[la, lb] = lval;
        for (auto &[rval, rcnt] : cntr) {
            auto &[ra, rb] = rval;
            int val = std::__gcd(la, ra) + std::__gcd(lb, rb);
            if (R[0] < val) {
                R = { val, lcnt * rcnt };
            }
            else if (R[0] == val) {
                R[1] += lcnt * rcnt;
            }
        }
    }

    return max(L, R);
}

void solve()
{
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        pa[i] = std::__gcd(pa[i - 1], a[i]);
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> b[i];
        pb[i] = std::__gcd(pb[i - 1], b[i]);
    }
    sa[n + 1] = sb[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        sa[i] = std::__gcd(sa[i + 1], a[i]);
        sb[i] = std::__gcd(sb[i + 1], b[i]);
    }

    auto [val, num] = cnt(1, n);
    std::cout << val << ' ' << num << '\n';
}

int main()
{
    // IOS;
    int t = 1;
    std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
#include<bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0)

using i64 = long long;
using i128 = __int128_t;

constexpr i64 Mod = 998244353, Inf = 1e18;
constexpr int N = 100, M = 1e7;

typedef std::array<i64, 2> infor;

void solve()
{
    int n = 0, x = 0;
    std::cin >> n >> x;
    std::vector m(n, std::array<infor, 2>{});
    for (auto &[a, b] : m) {
        std::cin >> a[0] >> a[1] >> b[0] >> b[1];
    }

    auto chk = [&](i64 mid) -> bool {
        i64 need = 0;
        for (int i = 0; i < n; i++) {
            auto [A, P] = m[i][0];
            auto [B, Q] = m[i][1];

            i64 res = 0x3f3f3f3f;
            for (int j = 0; j < B; j++) {
                res = std::min(res, P * j + (std::max(mid - A * j, 0ll) + B - 1) / B * Q);
            }
            for (int j = 0; j < A; j++) {
                res = std::min(res, Q * j + (std::max(mid - B * j, 0ll) + A - 1) / A * P);
            }

            need += res;
        }
        return need <= x;
    };
    int l = 0, r = 1e9;
    while (l <= r) {
        int mid = l + r >> 1;
        if (chk(mid)) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    std::cout << r << '\n';
}

int main()
{
    // IOS;
    int t = 1;
    // std::cin >> t;
    
    while (t--)
    {
        solve();
    }

    system("pause");

    return 0;
}
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
#define double long double

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

constexpr i64 Mod = 1e9 + 7;
constexpr int N = 1 << 20, MAX = 1e9; 

void build(int l, int r, int sl, int sr, std::vector<std::array<int, 2>> &a) {
    if (sl <= l && r <= sr) {
        a.push_back({ l, r });
        return;
    }
    
    int m = l + r >> 1;
    if (m > sl) {
        build(l, m, sl, sr, a);
    }
    if (m < sr) {
        build(m, r, sl, sr, a);
    }
    return;
}

void solve() {
    int l1, r1, l2, r2;
    std::cin >> l1 >> r1 >> l2 >> r2;
    std::vector<std::array<int, 2>> X, Y;

    build(0, N, l1, r1, X);
    build(0, N, l2, r2, Y);

    int ans = 0;
    for (auto &[x1, x2] : X) {
        int lx = x2 - x1;
        for (auto &[y1, y2] : Y) {
            int ly = y2 - y1;
            ans += std::max(lx, ly) / std::min(lx, ly);
        }
    }
    std::cout << ans << '\n';

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

    return 0;
}
